#include "Button.h"
#include "Input.h"

//======================================================================================================
Button::Button(const SDL_Point& position,
	const SDL_Point& dimension,
	const SDL_Rect& textureDimension,
	const std::string& filename,
	bool hasClickState,
	int rowIndex) : rowIndex(rowIndex), hasClickState(hasClickState)
{
	texture.Load(filename, filename);
	texture.SetDimension(dimension.x, dimension.y);
	texture.SetSourceDimension(textureDimension.x,
		textureDimension.y,
		textureDimension.w,
		textureDimension.h);
	texture.SetTexture(filename);

	this->position = position;
	this->dimension = dimension;
	collider = { position.x, position.y, dimension.x, dimension.y };
}
//======================================================================================================
void Button::Update(int deltaTime)
{
	auto mousePosition = Input::Instance()->GetMousePosition();
	auto isMouseClicked = Input::Instance()->IsMouseClicked(HM_MOUSE_LEFT);

	if (SDL_PointInRect(&mousePosition, &collider))
	{
		if (isMouseClicked && hasClickState)
		{
			state = State::Clicked;
		}

		else
		{
			state = State::Hover;
		}
	}

	else
	{
		state = State::Default;
	}
}
//======================================================================================================
bool Button::Render()
{
	texture.SetCel(static_cast<int>(state), rowIndex);
	texture.Render(position.x, position.y);
	return true;
}