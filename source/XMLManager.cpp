#include "../include/XMLManager.h"

// #define CHECK_XML(result) XMLManager::check_xml(result, __LINE__, __FILE__)

namespace evolver
{
	XMLManager::XMLManager(const char* xmlFilename) :
		baseXMLFile("xml/"),
		filename(xmlFilename)
	{
		std::string file = xmlFilename;

		if (strstr(xmlFilename, ".xml") != 0)
		{
			file += ".xml";
		}

		currentXMLFile.assign(baseXMLFile.string() + file);

		if (std::filesystem::exists(currentXMLFile))
		{
			document.load_file(currentXMLFile.string().c_str());
		}
	}

	void XMLManager::Save()
	{
		document.save_file(currentXMLFile.string().c_str());
	}

	void XMLManager::AddVec2(const char* nodeName, glm::vec2 vector)
	{
		node = document.append_child(nodeName);

		attribute = node.append_attribute("x");
		attribute.set_value(vector.x);

		attribute = node.append_attribute("y");
		attribute.set_value(vector.y);
	}

	void XMLManager::AddVec3(const char* nodeName, glm::vec3 vector)
	{
		node = document.append_child(nodeName);

		attribute = node.append_attribute("x");
		attribute.set_value(vector.x);

		attribute = node.append_attribute("y");
		attribute.set_value(vector.y);

		attribute = node.append_attribute("z");
		attribute.set_value(vector.z);
	}

	void XMLManager::AddVec4(const char* nodeName, glm::vec4 vector)
	{
		node = document.append_child(nodeName);

		attribute = node.append_attribute("x");
		attribute.set_value(vector.x);

		attribute = node.append_attribute("y");
		attribute.set_value(vector.y);

		attribute = node.append_attribute("z");
		attribute.set_value(vector.z);

		attribute = node.append_attribute("w");
		attribute.set_value(vector.w);
	}

	void XMLManager::AddShaderInfo(const char* nodeName, const char* filename, const char* compiledname)
	{
		if (!baseShaderNode)
		{
			baseShaderNode = document.append_child("Shader");
		}

		node = baseShaderNode.append_child(nodeName);

		attribute = node.append_attribute("filename");
		attribute.set_value(filename);

		attribute = node.append_attribute("compiled_name");
		attribute.set_value(compiledname);
	}

	void XMLManager::AddModelInfo(const char* nodeName, const char* filename, int count)
	{
		if (!baseModelNode)
		{
			baseModelNode = document.append_child("Model");
		}

		node = baseModelNode.append_child(nodeName);

		attribute = node.append_attribute("filename");
		attribute.set_value(filename);

		attribute = node.append_attribute("count");
		attribute.set_value(count);
	}

	void XMLManager::AddTextureInfo(const char* nodeName, const char* filename, int width, int height, int channel)
	{
		if (!baseTextureNode)
		{
			baseTextureNode = document.append_child("Texture");
		}

		node = baseTextureNode.append_child(nodeName);

		attribute = node.append_attribute("filename");
		attribute.set_value(filename);

		attribute = node.append_attribute("width");
		attribute.set_value(width);

		attribute = node.append_attribute("height");
		attribute.set_value(height);

		attribute = node.append_attribute("channel");
		attribute.set_value(channel);
	}

	int XMLManager::GetInt(const char* nodeName)
	{
		int result = 0;

		result = document.child(nodeName).attribute("value").as_int();

		return result;
	}

	float XMLManager::GetFloat(const char* nodeName)
	{
		float result = 0.0f;

		result = document.child(nodeName).attribute("value").as_float();

		return result;
	}

	double XMLManager::GetDouble(const char* nodeName)
	{
		double result = 0.0f;

		result = document.child(nodeName).attribute("value").as_double();

		return result;
	}

	const char* XMLManager::GetText(const char* nodeName)
	{
		return document.child(nodeName).attribute("value").as_string();
	}

	std::tuple<const char*, const char*> XMLManager::GetShaderInfo(const char* nodeName)
	{
		std::tuple<const char*, const char*> result(
			baseShaderNode.child(nodeName).attribute("filename").as_string(),
			baseShaderNode.child(nodeName).attribute("compiled_name").as_string()
		);

		return result;
	}

	std::tuple<const char*, int> XMLManager::GetModelInfo(const char* nodeName)
	{
		std::tuple<const char*, int> result(
			baseModelNode.child(nodeName).attribute("filename").as_string(),
			baseModelNode.child(nodeName).attribute("count").as_int()
		);

		return result;
	}

	std::tuple<const char*, int, int, int> XMLManager::GetTextureInfo(const char* nodeName)
	{
		std::tuple<const char*, int, int, int> result(
			baseTextureNode.child(nodeName).attribute("filename").as_string(),
			baseTextureNode.child(nodeName).attribute("width").as_int(),
			baseTextureNode.child(nodeName).attribute("height").as_int(),
			baseTextureNode.child(nodeName).attribute("channel").as_int()
		);

		return result;
	}

	glm::vec2 XMLManager::GetVec2(const char* nodeName)
	{
		glm::vec2 result = { 0.f, 0.f };

		result.x = document.child(nodeName).attribute("x").as_float();
		result.y = document.child(nodeName).attribute("y").as_float();

		return result;
	}

	glm::vec3 XMLManager::GetVec3(const char* nodeName)
	{
		glm::vec3 result = { 0.f, 0.f, 0.0f };

		result.x = document.child(nodeName).attribute("x").as_float();
		result.y = document.child(nodeName).attribute("y").as_float();
		result.z = document.child(nodeName).attribute("z").as_float();

		return result;
	}

	glm::vec4 XMLManager::GetVec4(const char* nodeName)
	{
		glm::vec4 result = { 0.f, 0.f, 0.0f, 0.0f };

		result.x = document.child(nodeName).attribute("x").as_float();
		result.y = document.child(nodeName).attribute("y").as_float();
		result.z = document.child(nodeName).attribute("z").as_float();
		result.w = document.child(nodeName).attribute("w").as_float();

		return result;
	}
}