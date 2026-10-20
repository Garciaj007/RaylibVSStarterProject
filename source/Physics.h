#pragma once

#include <raylib.h>
#include <box2d/box2d.h>
#include <optional>

extern float PPM; // Pixel Per Meter
const int BOX2D_SHAPE_COUNT = 4;

// Convert meters <-> pixels
static inline Vector2 to_pixels(b2Vec2 v)
{
	return { v.x * PPM, v.y * PPM };
}
static inline b2Vec2 to_meters(Vector2 v)
{
	return { v.x / PPM, v.y / PPM };
}
static Vector2 world_to_screen(b2Vec2 v)
{
	return
	{
		GetScreenWidth() * 0.5f + v.x * PPM,   // origin at screen center
		GetScreenHeight() * 0.5f - v.y * PPM,   // flip Y: world-up → screen-up
	};
}

static void draw_body(b2BodyId body, Color color, Color wireframeColor = BLANK)
{
	b2Transform xf = b2Body_GetTransform(body);

	int n = b2Body_GetShapeCount(body);
	b2ShapeId shapes[BOX2D_SHAPE_COUNT];                       // bump if you use more
	b2Body_GetShapes(body, shapes, n);

	for (int i = 0; i < n; i++)
	{
		b2ShapeType t = b2Shape_GetType(shapes[i]);

		if (t == b2_polygonShape) {
			b2Polygon poly = b2Shape_GetPolygon(shapes[i]);
			Vector2 pts[B2_MAX_POLYGON_VERTICES];

			for (int v = 0; v < poly.count; v++) {
				b2Vec2 world = b2TransformPoint(xf, poly.vertices[v]);
				pts[v] = world_to_screen(world);
			}

			// Fill (triangle fan — safe because Box2D polys are convex)
			for (int v = 1; v < poly.count - 1; v++)
				DrawTriangle(pts[0], pts[v], pts[v + 1], color);

			// Outline
			for (int v = 0; v < poly.count; v++)
				DrawLineV(pts[v], pts[(v + 1) % poly.count], wireframeColor);

		}
		else if (t == b2_circleShape) {
			b2Circle c = b2Shape_GetCircle(shapes[i]);
			Vector2 p = world_to_screen(b2TransformPoint(xf, c.center));
			float r = c.radius * PPM;
			DrawCircleV(p, r, color);
			DrawCircleLinesV(p, r, wireframeColor);
		}
	}
}