#include "GameObject.h"


GameObject::GameObject(const CellPosition & pos)
{
	position = pos; // Sets Position
}
GameObject::GameObject()
{

}
CellPosition GameObject::GetPosition() const
{
	return position;
}
void GameObject::setPosition(CellPosition pos)
{
	position = pos;
}

void GameObject::Save(ofstream& Outfile, Type GOtype)
{

}
void GameObject:: Load(ifstream& Infile,Grid*pGrid)
{

}

GameObject::~GameObject()
{
}