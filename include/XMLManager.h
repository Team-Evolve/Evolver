#pragma once

#include "pugixml.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <iostream>
#include <filesystem>

namespace evolver
{
	class XMLManager
	{
	public:
		XMLManager(const char* xmlFilename);
		void Save();

		template<typename T>
		void AddSingleItem(const char* nodeName, T value)
		{
			node = document.append_child(nodeName);
			attribute = node.append_attribute("value");
			attribute.set_value(value);
		}

		template<typename T>
		void ChangeValue(const char* baseNode, const char* nodeName, const char* attribute, T value)
		{
			if (baseNode == nullptr && document.child(nodeName))
			{
				document.child(nodeName).attribute(attribute).set_value(value);
			}
			else if (baseNode != nullptr && document.child(baseNode))
			{
				baseNode.child(nodeName).attribute(attribute).set_value(value);
			}
		}

		void AddVec2(const char* nodeName, glm::vec2 vector);
		void AddVec3(const char* nodeName, glm::vec3 vector);
		void AddVec4(const char* nodeName, glm::vec4 vector);

		void AddShaderInfo(const char* nodeName, const char* filename, const char* compiledname);

		void AddModelInfo(const char* nodeName, const char* filename, int count);

		void AddTextureInfo(const char* nodeName, const char* filename, int width, int height, int channel);

		int GetInt(const char* nodeName);
		float GetFloat(const char* nodeName);
		double GetDouble(const char* nodeName);
		const char* GetText(const char* nodeName);

		std::tuple<const char*, const char*> GetShaderInfo(const char* nodeName);
		std::tuple<const char*, int> GetModelInfo(const char* nodeName);
		std::tuple<const char*, int, int, int> GetTextureInfo(const char* nodeName);

		glm::vec2 GetVec2(const char* nodeName);
		glm::vec3 GetVec3(const char* nodeName);
		glm::vec4 GetVec4(const char* nodeName);

	private:
		/*
		void check_xml(pugi::xml_parse_result result, int line, const char* filename)
		{
			switch (result)
			{
			case pugi::xml_parse_status::status_file_not_found:
				std::cout << "status_file_not_found : " << line << " " << filename << "\n";
				break;
			case pugi::xml_parse_status::status_io_error:
				std::cout << "status_io_error : " << line << " " << filename << "\n";
				break;
			case pugi::xml_parse_status::status_out_of_memory:
				std::cout << "status_out_of_memory : " << line << " " << filename << "\n";
				break;
			case pugi::xml_parse_status::status_internal_error:
				std::cout << "status_internal_error : " << line << " " << filename << "\n";
				break;
			case pugi::xml_parse_status::status_unrecognized_tag:
				std::cout << "status_unrecognized_tag : " << line << " " << filename << "\n";
				break;
			case pugi::xml_parse_status::status_bad_pi:
				std::cout << "status_bad_pi : " << line << " " << filename << "\n";
				break;
			case pugi::xml_parse_status::status_bad_comment:
				std::cout << "status_bad_comment : " << line << " " << filename << "\n";
				break;
			case pugi::xml_parse_status::status_bad_cdata:
				std::cout << "status_bad_cdata : " << line << " " << filename << "\n";
				break;
			case pugi::xml_parse_status::status_bad_doctype:
				std::cout << "status_bad_doctype : " << line << " " << filename << "\n";
				break;
			case pugi::xml_parse_status::status_bad_pcdata:
				std::cout << "status_bad_pcdata : " << line << " " << filename << "\n";
				break;
			case pugi::xml_parse_status::status_bad_start_element:
				std::cout << "status_bad_start_element : " << line << " " << filename << "\n";
				break;
			case pugi::xml_parse_status::status_bad_attribute:
				std::cout << "status_bad_attribute : " << line << " " << filename << "\n";
				break;
			case pugi::xml_parse_status::status_bad_end_element:
				std::cout << "status_bad_end_element : " << line << " " << filename << "\n";
				break;
			case pugi::xml_parse_status::status_end_element_mismatch:
				std::cout << "status_end_element_mismatch : " << line << " " << filename << "\n";
				break;
			case pugi::xml_parse_status::status_append_invalid_root:
				std::cout << "XML_ERROR_PARSING : " << line << " " << filename << "\n";
				break;
			case pugi::xml_parse_status::status_no_document_element:
				std::cout << "status_no_document_element : " << line << " " << filename << "\n";
				break;
			case pugi::xml_parse_status::status_ok:
				break;
			}
		}
		*/

	private:
		pugi::xml_document document;
		pugi::xml_node node;
		pugi::xml_parse_result result;
		pugi::xml_attribute attribute;

		pugi::xml_node baseShaderNode;
		pugi::xml_node baseModelNode;
		pugi::xml_node baseTextureNode;

		std::filesystem::path baseXMLFile;
		std::filesystem::path currentXMLFile;
		std::string filename;
	};
}
