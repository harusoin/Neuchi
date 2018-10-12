/**
* @file      NusonController.h
* @brief     This class is controller of NUSON file.
* @author    Shin Oura
* @copyright 2018 Shin Oura
*/
#ifndef NEUCHI_NUSONCONTROLLER_H
#define NEUCHI_NUSONCONTROLLER_H

#include <string>
#include <optional>
#include <vector>
#include <boost/property_tree/ptree.hpp>

namespace neuchi
{
namespace nuson
{
const std::vector<std::string> kSupportedNusonVersion = {"0.1"};
const int kDefaultResolution = 240;
const int kDefaultWidthResolution = 120;

struct NusonNoteData
{
	std::string type;
	int x;
	int y;
	int l;
};
struct NusonObjectData
{
	std::string type;
	std::vector<NusonNoteData>* notes;
};
struct NusonEnemyData
{
	std::string name;
	int level;
	std::string attribute;
	int hit_point;
};
struct NusonInfoData
{
	std::string mode_hint;
	std::string title;
	std::string artist;
	std::string notes_designer;
	std::string level;
	std::string genre;
	std::string chart_name;
	double init_bpm;
	std::string back_image;
	std::string banner_image;
	std::string preview_music;
	int resolution;
	int width_resolution;
	std::string copyright;
};

class NusonController
{
public:
	NusonController() : current_nuson_file_path(boost::none)
					, current_nuson_version(kSupportedNusonVersion.back()){}
	NusonController(const std::string &filepath);
	NusonController(const NusonController &from) {}
	~NusonController();

	bool CheckSyntax();
	void ReadNusonFile(const std::string &filepath);
	bool ReadNusonFile();
	void WriteNusonFile(const std::string &filepath);
	bool WriteNusonFile();
	std::string GetNusonVersion();
	NusonInfoData GetNusonInfoData();
	NusonEnemyData GetNusonEnemyData();
private:
	boost::optional<std::string> current_nuson_file_path;
	boost::property_tree::ptree current_nuson_data;
	std::string current_nuson_version;
};
}
}
#endif // NEUCHI_NUSONCONTROLLER_H
