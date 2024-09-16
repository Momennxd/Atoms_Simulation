#pragma once
#include "main_includes.h"
#include "filesystem.h"




	static unordered_map<string, string> SettingsMap = FileSystem::GetConfigSettingsMap(CONFIG_FILEPATH);


	/// <summary>
	/// Represents the number of atoms that spawn each second.
	/// </summary>
	static int atoms_num_persec = stoi(SettingsMap[ATOMS_SPAWING_NUMBERS_PERSEC_NAME]);
	



	static int atoms_speed = stoi(SettingsMap[ATOMS_SPEED_NAME]);



	/// <summary>
	/// Represents the max number of atoms in the current scene.
	/// </summary>
	static int atoms_max = stoi(SettingsMap[MAX_NUMBER_ATOMS_NAME]);


	static int atom_radias = stoi(SettingsMap[ATOM_RADIAS]);




	






