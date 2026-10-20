#pragma once

#include <iostream>
#include <box2d/box2d.h>

#include "Scene.h"
#include "Physics.h"

class SceneThree : public Scene
{
	b2WorldId worldId;
	b2BodyId bodyId, groundBodyId;

public:
	SceneThree()
	{
		b2WorldDef worldDef = b2DefaultWorldDef();
		worldDef.gravity = { 0.0f, -10.0f };
		worldId = b2CreateWorld(&worldDef);

		b2BodyDef groundBodyDef = b2DefaultBodyDef();
		groundBodyDef.position = { 0.0f, -10.0f };
		groundBodyId = b2CreateBody(worldId, &groundBodyDef);
		b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);
		b2ShapeDef groundShapeDef = b2DefaultShapeDef();
		b2CreatePolygonShape(groundBodyId, &groundShapeDef, &groundBox);

		b2BodyDef bodyDef = b2DefaultBodyDef();
		bodyDef.type = b2_dynamicBody;
		bodyDef.position = { 0.0f, 20.0f };
		bodyId = b2CreateBody(worldId, &bodyDef);
		b2Polygon dynamicBox = b2MakeBox(2.0f, 2.0f);
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeDef.density = 1.0f;
		shapeDef.material.friction = 0.3f;
		b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
	}

	~SceneThree()
	{
		b2DestroyWorld(worldId);
	}

	std::string_view get_name() const override { return "Scene Three"; }

	void resize(int width, int height) override {}

	void update(float time, float dt) override
	{
		b2World_Step(worldId, dt, 4);
	}

	void render() override
	{
		ClearBackground(LIGHTGRAY);
		DrawText(get_name().data(), 10, 10, 20, BLUE);
		draw_body(bodyId, BLUE);
		draw_body(groundBodyId, DARKGRAY);
	}
};


struct SceneThreeFactory : public SceneFactory
{
	std::unique_ptr<Scene> create() override { return std::make_unique<SceneThree>(); }
};