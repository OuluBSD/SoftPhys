#include <SoftPhys/SoftPhys.h>

using namespace Upp;
using namespace SoftPhys;

namespace {

void TestWorldAndBody()
{
	Cout() << "TestWorldAndBody: Starting..." << EOL;

	World world;
	vec3 grav(0.0f, -9.82f, 0.0f);
	world.SetGravity(grav);

	Body body;
	body.Create();
	vec3 init_pos(0.0f, 10.0f, 0.0f);
	body.SetPosition(init_pos);
	body.SetMass(5.0f);
	body.SetLinearVelocity(vec3(0.0f, 1.0f, 0.0f));
	world.CreateBody(body);

	ASSERT(body.GetPosition()[1] == 10.0f);
	ASSERT(body.world == &world);
	ASSERT(body.mass.mass == 5.0f);

	// Test simulation via Space and Particle
	Space space;
	space.SetWorld(world);

	Particle particle;
	particle.SetPosition(vec3(0.0f, 10.0f, 0.0f));
	particle.SetMass(1.0f);
	space.Add(particle);

	ASSERT(particle.GetPosition()[1] == 10.0f);

	// Simulate 60 steps at 60Hz
	for(int i = 0; i < 60; i++) {
		world.Step(1.0f / 60.0f);
	}

	vec3 pos = particle.GetPosition();
	Cout() << "Particle position after 1 second: y = " << pos[1] << EOL;
	ASSERT(pos[1] < 10.0f);
	ASSERT(std::isfinite(pos[1]));

	Cout() << "TestWorldAndBody: Passed!" << EOL;
}

void TestPhysicsSystemAndCloth()
{
	Cout() << "TestPhysicsSystemAndCloth: Starting..." << EOL;

	PhysicsSystem sys;

	Cloth cloth;
	vec3 cloth_pos(0.0f, 5.0f, 0.0f);
	cloth.Initialize(4, 0.5f, cloth_pos);
	cloth.SetStructuralSprings(20.0f, 0.2f);
	cloth.SetParticleMass(0.1f);

	sys.AddCloth(&cloth);

	// Step system
	for(int i = 0; i < 30; i++) {
		sys.Update(0.016f);
	}

	sys.ClearCloths();

	Cout() << "TestPhysicsSystemAndCloth: Passed!" << EOL;
}

void TestQuadTree()
{
	Cout() << "TestQuadTree: Starting..." << EOL;

	FixedRectangle world_bounds(vec2(0.0f, 0.0f), vec2(1000.0f, 1000.0f));
	QuadTree tree(world_bounds);

	int dummy1 = 1;
	int dummy2 = 2;
	QuadTreeData d1(&dummy1, FixedRectangle(vec2(10.0f, 10.0f), vec2(50.0f, 50.0f)));
	QuadTreeData d2(&dummy2, FixedRectangle(vec2(500.0f, 500.0f), vec2(100.0f, 100.0f)));

	tree.Insert(d1);
	tree.Insert(d2);

	Vector<QuadTreeData*> q1 = tree.Query(FixedRectangle(vec2(0.0f, 0.0f), vec2(100.0f, 100.0f)));
	ASSERT(q1.GetCount() >= 1);
	bool found1 = false;
	bool found2 = false;
	for(QuadTreeData* it : q1) {
		if(it->object == &dummy1) found1 = true;
		if(it->object == &dummy2) found2 = true;
	}
	ASSERT(found1);
	ASSERT(!found2);

	Vector<QuadTreeData*> q2 = tree.Query(FixedRectangle(vec2(450.0f, 450.0f), vec2(200.0f, 200.0f)));
	found2 = false;
	for(QuadTreeData* it : q2) {
		if(it->object == &dummy2) found2 = true;
	}
	ASSERT(found2);

	Cout() << "TestQuadTree: Passed!" << EOL;
}

}

CONSOLE_APP_MAIN
{
	Cout() << "========================================" << EOL;
	Cout() << "Running SoftPhys Automated Unit Tests" << EOL;
	Cout() << "========================================" << EOL;

	TestWorldAndBody();
	TestPhysicsSystemAndCloth();
	TestQuadTree();

	Cout() << "========================================" << EOL;
	Cout() << "ALL SOFTPHYS TESTS PASSED!" << EOL;
	Cout() << "========================================" << EOL;
}
