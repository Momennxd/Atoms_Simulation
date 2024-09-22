#pragma once
#include "main_includes.h"
#include "filesystem.h"



	static unordered_map<string, string> SettingsMap = FileSystem::GetConfigSettingsMap(CONFIG_FILEPATH);


	/// <summary>
	/// Represents the number of atoms that spawn each second.
	/// </summary>
	static double atoms_num_persec = stod(SettingsMap[ATOMS_SPAWING_NUMBERS_PERSEC_NAME]);
	



	static double atoms_speed = stod(SettingsMap[ATOMS_SPEED_NAME]);



	/// <summary>
	/// Represents the max number of atoms in the current scene.
	/// </summary>
	static int atoms_max =  std::min(stoi(SettingsMap[MAX_NUMBER_ATOMS_NAME]), MAX_HANDLED_ATOMS);


	static double atom_radias = stod(SettingsMap[ATOM_RADIAS]);




	






