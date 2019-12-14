
#include "Game.h"

#include "Draws.h"

#include "Globals.h"

//#define DEBUG_COLLISION

bool IsInteractingPoint(BoxCollider col, Point point) {
	// offset is used as position

	return point.x < col.offset.x + col.size.x && point.x > col.offset.x && point.y < col.offset.y + col.size.y && point.y > col.offset.y;

}


bool IsInteracting(BoxCollider col1, BoxCollider col2) {
	// offset is used as position


	return col1.offset.x <= col2.offset.x + col2.size.x &&
		col1.offset.x + col1.size.x >= col2.offset.x &&
		col1.offset.y <= col2.offset.y + col2.size.y &&
		col1.offset.y + col1.size.y >= col2.offset.y;

}



GameObjectList GetInteractsOfCollider(BoxCollider col1, Point position)
{
	GameObjectList list;
	initialize_game_object_list(&list);

	col1.offset.x += position.x;
	col1.offset.y += position.y;

#ifdef DEBUG_COLLISION
	if (renderable_state)
		DrawRectangle((Rect) {
		col1.offset.x - (camera->position.x - camera->width / 2), col1.offset.y - (camera->position.y - camera->height / 2),
			col1.size.x, col1.size.y
	}, (Color) { 255, 0, 0, 255 });
#endif

	for (int i = 0; i < GameObjects.Count; i++)
	{
		GameObject* go = GameObjects.List[i];

		BoxCollider col2 = go->collider;
		col2.offset.x += go->transform->position.x;
		col2.offset.y += go->transform->position.y;

		if (col1.offset.x == col2.offset.x && col1.offset.y == col2.offset.y) continue;

		if (IsInteracting(col1, col2))
			add_game_object_to_list(&list, go);
	}

	return list;
}

GameObjectList GetInteracts(GameObject* object)
{
	GameObjectList list;
	initialize_game_object_list(&list);

	BoxCollider col1 = object->collider;
	col1.offset.x += object->transform->position.x;
	col1.offset.y += object->transform->position.y;
	col1.size.x *= object->transform->scale.x;
	col1.size.y *= object->transform->scale.y;

#ifdef DEBUG_COLLISION
	if (renderable_state)
		DrawRectangle((Rect) {
		col1.offset.x - (camera->position.x - camera->width / 2), col1.offset.y - (camera->position.y - camera->height / 2),
			col1.size.x, col1.size.y
	}, (Color) { 255, 0, 0, 255 });
#endif

	for (int i = 0; i < GameObjects.Count; i++)
	{
		GameObject* go = GameObjects.List[i];

		if (go == object) continue;

		BoxCollider col2 = go->collider;
		col2.offset.x += go->transform->position.x;
		col2.offset.y += go->transform->position.y;
		col2.size.x *= go->transform->scale.x;
		col2.size.y *= go->transform->scale.y;




		if (IsInteracting(col1, col2))
		{
			add_game_object_to_list(&list, go);

#ifdef DEBUG_COLLISION
			if (renderable_state)
				DrawRectangle((Rect) {
				col2.offset.x - (camera->position.x - camera->width / 2), col2.offset.y - (camera->position.y - camera->height / 2),
					col2.size.x, col2.size.y
			}, (Color) { 255, 0, 0, 255 });
#endif
		}
		else
		{
#ifdef DEBUG_COLLISION
			if (renderable_state)

				DrawRectangle((Rect) {
				col2.offset.x - (camera->position.x - camera->width / 2), col2.offset.y - (camera->position.y - camera->height / 2),
					col2.size.x, col2.size.y
			}, (Color) { 0, 255, 0, 255 });
#endif
		}

			
	}

	return list;
}


GameObjectList GetInteractsExceptLayer(GameObject* object, int layer_mask)
{
	GameObjectList list;
	initialize_game_object_list(&list);

	BoxCollider col1 = object->collider;
	col1.offset.x += object->transform->position.x;
	col1.offset.y += object->transform->position.y;
	col1.size.x *= object->transform->scale.x;
	col1.size.y *= object->transform->scale.y;

#ifdef DEBUG_COLLISION
	if (renderable_state)

		DrawRectangle((Rect) {
		col1.offset.x - (camera->position.x - camera->width / 2), col1.offset.y - (camera->position.y - camera->height / 2),
			col1.size.x, col1.size.y
	}, (Color) { 255, 0, 0, 255 });
#endif

	for (int i = 0; i < GameObjects.Count; i++)
	{
		GameObject* go = GameObjects.List[i];

		if (go == object) continue;

		//int objLayerMask = (1 << go->layer);

		if ((go->layer & layer_mask)) continue;


		BoxCollider col2 = go->collider;
		col2.offset.x += go->transform->position.x;
		col2.offset.y += go->transform->position.y;
		col2.size.x *= go->transform->scale.x;
		col2.size.y *= go->transform->scale.y;




		if (IsInteracting(col1, col2))
		{
			add_game_object_to_list(&list, go);

#ifdef DEBUG_COLLISION
			if (renderable_state)

			DrawRectangle((Rect) {
				col2.offset.x - (camera->position.x - camera->width / 2), col2.offset.y - (camera->position.y - camera->height / 2),
					col2.size.x, col2.size.y
			}, (Color) { 255, 0, 0, 255 });
#endif
		}
		else
		{
#ifdef DEBUG_COLLISION
			if (renderable_state)

			DrawRectangle((Rect) {
				col2.offset.x - (camera->position.x - camera->width / 2), col2.offset.y - (camera->position.y - camera->height / 2),
					col2.size.x, col2.size.y
			}, (Color) { 0, 255, 0, 255 });
#endif
		}


	}

	return list;
}


GameObjectList GetInteractsOnlyLayer(GameObject* object, int layer_mask)
{
	GameObjectList list;
	initialize_game_object_list(&list);

	BoxCollider col1 = object->collider;
	col1.offset.x += object->transform->position.x;
	col1.offset.y += object->transform->position.y;
	col1.size.x *= object->transform->scale.x;
	col1.size.y *= object->transform->scale.y;

#ifdef DEBUG_COLLISION
	if (renderable_state)

		DrawRectangle((Rect) {
		col1.offset.x - (camera->position.x - camera->width / 2), col1.offset.y - (camera->position.y - camera->height / 2),
			col1.size.x, col1.size.y
	}, (Color) { 255, 0, 0, 255 });
#endif

	for (int i = 0; i < GameObjects.Count; i++)
	{
		GameObject* go = GameObjects.List[i];

		if (go == object) continue;

		//int objLayerMask = (1 << go->layer);

		if (!(go->layer & layer_mask)) continue;

		BoxCollider col2 = go->collider;
		col2.offset.x += go->transform->position.x;
		col2.offset.y += go->transform->position.y;
		col2.size.x *= go->transform->scale.x;
		col2.size.y *= go->transform->scale.y;




		if (IsInteracting(col1, col2))
		{
			add_game_object_to_list(&list, go);

#ifdef DEBUG_COLLISION
			if (renderable_state)

				DrawRectangle((Rect) {
				col2.offset.x - (camera->position.x - camera->width / 2), col2.offset.y - (camera->position.y - camera->height / 2),
					col2.size.x, col2.size.y
			}, (Color) { 255, 0, 0, 255 });
#endif
		}
		else
		{
#ifdef DEBUG_COLLISION
			if (renderable_state)

				DrawRectangle((Rect) {
				col2.offset.x - (camera->position.x - camera->width / 2), col2.offset.y - (camera->position.y - camera->height / 2),
					col2.size.x, col2.size.y
			}, (Color) { 0, 255, 0, 255 });
#endif
		}


	}

	return list;
}


Vector2 collider_center(BoxCollider collider)
{
	Vector2 center = { collider.size.x / 2 + collider.offset.x, collider.size.y / 2 + collider.offset.y };

	return center;
}