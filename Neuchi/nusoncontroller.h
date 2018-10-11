/**
* @file      NusonController.h
* @brief     This class is controller of NUSON file.
* @author    Shin Oura
* @copyright 2018 Shin Oura
*/
#ifndef NEUCHI_NUSONCONTROLLER_H
#define NEUCHI_NUSONCONTROLLER_H

#include <string>
#include <memory>
#include <vector>


namespace neuchi
{
namespace nuson
{

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
struct NusonData
{
	double version;
	struct
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

	}info;
	struct
	{
		std::string name;
		int level;
		std::string attribute;
		int hit_point;
	}enemy;
	std::vector<NusonObjectData>* objects;
	NusonData() : objects(nullptr) {};
	~NusonData() {
		if (objects != nullptr)
		{
			for (auto o : *objects) {
				delete o.notes;
			}
		}
	}
private:
	void operator =(const NusonData& src) {}
	NusonData(const NusonData& src) {}
};

class NusonController
{
public:
	NusonController() {}
	NusonController(const NusonController &from) {}
	void LoadNusonFile(const std::string &filename);
	~NusonController();
private:
	std::unique_ptr<NusonData> current_nuson_data;
};
}
}
#endif // NEUCHI_NUSONCONTROLLER_H
