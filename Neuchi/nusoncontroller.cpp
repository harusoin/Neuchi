#include "nusoncontroller.h"
#include <boost/property_tree/json_parser.hpp>

using namespace boost::property_tree;
using namespace neuchi::nuson;

template<typename T>
T PtreeToNusonData(const ptree &nusontree, const std::string &accessor,
	const boost::optional<T> initial = boost::none) {

	if (boost::optional<T> value = nusontree.get_optional<T>(accessor)) {
		return value.get();
	}
	else {
		if (initial) {
			return initial.get();
		}
		throw std::runtime_error("undefined " + accessor);
	}
}

bool NusonController::CheckSyntax()
{
	if (boost::optional<std::string> value = current_nuson_data.get_optional<std::string>("version")) {
		std::string y = value.get();
		return std::any_of(kSupportedNusonVersion.begin(), kSupportedNusonVersion.end(), [&y](std::string x) { return x == y; });
	}
	return false;
}

void NusonController::ReadNusonFile(const std::string &filepath)
{
	try
	{
		read_json(filepath, current_nuson_data);
		if (!CheckSyntax()) throw std::runtime_error("NUSON file syntax error");
	}
	catch (boost::property_tree::json_parser_error& e)
	{
		throw;
	}
	catch (std::runtime_error& e)
	{
		throw;
	}
}

bool NusonController::ReadNusonFile()
{
	if (current_nuson_file_path == boost::none) return false;
	try
	{
		ReadNusonFile(current_nuson_file_path.get());
	}
	catch (boost::property_tree::json_parser_error& e)
	{
		throw;
	}
	return true;
}

void NusonController::WriteNusonFile(const std::string & filepath)
{
	try
	{
		write_json(filepath, current_nuson_data);
	}
	catch (boost::property_tree::json_parser_error& e)
	{
		throw;
	}
}

bool NusonController::WriteNusonFile()
{
	if (current_nuson_file_path == boost::none) return false;
	try
	{
		WriteNusonFile(current_nuson_file_path.get());
	}
	catch (boost::property_tree::json_parser_error& e)
	{
		throw;
	}
	return true;
}

std::string NusonController::GetNusonVersion()
{
	return current_nuson_version;
}

NusonInfoData NusonController::GetNusonInfoData()
{
	NusonInfoData d;
	try
	{
		d.mode_hint = PtreeToNusonData <std::string>(current_nuson_data, "info.mode_hint", std::string(""));
		d.title = PtreeToNusonData <std::string>(current_nuson_data, "info.title", std::string(""));
		d.artist = PtreeToNusonData <std::string>(current_nuson_data, "info.artist", std::string(""));
		d.notes_designer = PtreeToNusonData <std::string>(current_nuson_data, "info.notes_designer", std::string(""));
		d.level = PtreeToNusonData <std::string>(current_nuson_data, "info.level", std::string(""));
		d.genre = PtreeToNusonData <std::string>(current_nuson_data, "info.genre", std::string(""));
		d.chart_name = PtreeToNusonData <std::string>(current_nuson_data, "info.chart_name", std::string(""));
		d.init_bpm = PtreeToNusonData <double>(current_nuson_data, "info.init_bpm", 0);
		d.back_image = PtreeToNusonData <std::string>(current_nuson_data, "info.back_image", std::string(""));
		d.banner_image = PtreeToNusonData <std::string>(current_nuson_data, "info.banner_image", std::string(""));
		d.preview_music = PtreeToNusonData <std::string>(current_nuson_data, "info.preview_music", std::string(""));
		d.resolution = PtreeToNusonData <int>(current_nuson_data, "info.resolution", kDefaultResolution);
		d.width_resolution = PtreeToNusonData <int>(current_nuson_data, "info.width_resolution", kDefaultWidthResolution);
		d.copyright = PtreeToNusonData <std::string>(current_nuson_data, "info.copyright", std::string(""));
	}
	catch (boost::property_tree::json_parser_error& e)
	{
		throw;
	}
	return d;
}

NusonEnemyData NusonController::GetNusonEnemyData()
{
	NusonEnemyData d;
	try
	{
		d.name = PtreeToNusonData <std::string>(current_nuson_data, "enemy.name", std::string(""));
		d.level = PtreeToNusonData <int>(current_nuson_data, "enemy.level", 0);
		d.attribute = PtreeToNusonData <std::string>(current_nuson_data, "enemy.attribute", std::string(""));
		d.hit_point = PtreeToNusonData <int>(current_nuson_data, "enemy.hit_point", 0);
	}
	catch (const std::exception&)
	{
		throw;
	}
	return d;
}

NusonController::NusonController(const std::string &filepath)
{
	current_nuson_file_path = filepath;
	try
	{
		ReadNusonFile(filepath);
	}
	catch (boost::property_tree::json_parser_error& e)
	{
		throw;
	}
}

NusonController::~NusonController()
{
}
