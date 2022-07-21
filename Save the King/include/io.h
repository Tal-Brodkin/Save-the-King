#pragma once


const float VELOCITY = 2.0;

enum ObjectType
{
	KingObject = 'K',
	MageObject = 'M',
	WarriorObject = 'W',
	ThiefObject = 'T',
	WallObject = '=',
	GateObject = '#',
	FireObject = '*',
	OrcObject = '!',
	KeyObject = 'F',
	DwarfObject = '^',
	PortalObject = 'X',
	ThroneObject = '@'
};

enum SoundTypes
{
	hit_wall,
	open_door,
	locked_door,
	take_gift,
	sword,
	teleportation,
	fire_extinguish,
	key_pickup,
	orc_groan,
	level_won,
	time_over,
	menu_hover,
	menu_click,
	music,
	step,
	burn
};

enum TextureTypes
{
	king,
	mage,
	warrior,
	thief,
	wall,
	gate,
	fire,
	orc,
	key,
	teleport,
	throne,
	dwarf,
	gift,
	background,
	back
};