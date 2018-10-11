#include "nusoncontroller.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace boost::property_tree;
using namespace neuchi::nuson;

template<typename T>
T PtreeToNusonData(const ptree &nusontree, std::string accessor,
	boost::optional<T> initial = boost::none) {

	if (boost::optional<T> value = nusontree.get_optional<T>(accessor)) {
		return value.get();
	}
	else {
		if (initial) {
			return initial.get();
		}
		throw "undefined " + accessor;
	}
}

void NusonController::LoadNusonFile(const std::string &filename)
{
	std::unique_ptr<NusonData> temp_nuson_data(new NusonData);
	read_json(filename, current_nuson_data);

	try
	{
		temp_nuson_data->version = PtreeToNusonData<double>(current_nuson_raw_data, "version");
		temp_nuson_data->info.mode_hint = PtreeToNusonData<std::string>(current_nuson_raw_data, "info.mode_hint");
		temp_nuson_data->info.title = PtreeToNusonData<std::string>(current_nuson_raw_data, "info.title");
		temp_nuson_data->info.artist = PtreeToNusonData<std::string>(current_nuson_raw_data, "info.artist");
		temp_nuson_data->info.notes_designer = PtreeToNusonData<std::string>(current_nuson_raw_data, "info.notes_designer");
		temp_nuson_data->info.level = PtreeToNusonData<std::string>(current_nuson_raw_data, "info.level");
		temp_nuson_data->info.genre = PtreeToNusonData<std::string>(current_nuson_raw_data, "info.genre");
		temp_nuson_data->info.chart_name = PtreeToNusonData<std::string>(current_nuson_raw_data, "info.chart_name");
		temp_nuson_data->info.init_bpm = PtreeToNusonData<double>(current_nuson_raw_data, "info.init_bpm");
		temp_nuson_data->info.back_image = PtreeToNusonData<std::string>(current_nuson_raw_data, "info.back_image", boost::optional<std::string>(""));
		temp_nuson_data->info.banner_image = PtreeToNusonData<std::string>(current_nuson_raw_data, "info.banner_image", boost::optional<std::string>(""));
		temp_nuson_data->info.preview_music = PtreeToNusonData<std::string>(current_nuson_raw_data, "info.preview_music", boost::optional<std::string>(""));
		temp_nuson_data->info.resolution = PtreeToNusonData<int>(current_nuson_raw_data, "info.resolution");
		temp_nuson_data->info.width_resolution = PtreeToNusonData<int>(current_nuson_raw_data, "info.width_resolution");
		temp_nuson_data->info.copyright = PtreeToNusonData<std::string>(current_nuson_raw_data, "info.copyright", boost::optional<std::string>(""));
		temp_nuson_data->enemy.name = PtreeToNusonData<std::string>(current_nuson_raw_data, "enemy.name");
		temp_nuson_data->enemy.level = PtreeToNusonData<int>(current_nuson_raw_data, "enemy.level");
		temp_nuson_data->enemy.attribute = PtreeToNusonData<std::string>(current_nuson_raw_data, "enemy.attribute");
		temp_nuson_data->enemy.hit_point = PtreeToNusonData<int>(current_nuson_raw_data, "enemy.hit_point");
		temp_nuson_data->objects = new std::vector<NusonObjectData>;
		for (auto child : current_nuson_raw_data.get_child("objects")) {
			NusonObjectData t;
			const ptree& objects = child.second;
			t.type = PtreeToNusonData<std::string>(objects, "type");
			t.notes = new std::vector<NusonNoteData>;
			for (auto child_object : current_nuson_raw_data.get_child("notes")) {
				NusonNoteData t2;
				const ptree& objects = child.second;
				t2.type = PtreeToNusonData<std::string>(objects, "type");
				t2.x = PtreeToNusonData<int>(objects, "x", 0);
				t2.y = PtreeToNusonData<int>(objects, "y", 0);
				t2.l = PtreeToNusonData<int>(objects, "l", 0);
				t.notes->push_back(t2);
			}
			temp_nuson_data->objects->push_back(t);
		}
	}
	catch (std::string e)
	{
		throw;
	}
	current_nuson_data = std::move(temp_nuson_data);
}

NusonController::~NusonController()
{
}
