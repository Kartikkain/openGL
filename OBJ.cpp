#include "OBJ.h"

Model::Model(const char* file)
{
	std::string text = get_file_content(file);
	JSON = json::parse(text);
	Model::file = file;
	data = getdata();
	traversenodes(0);
}

std::vector<unsigned char> Model::getdata()
{
	std::string bytetext;
	std::string uri = JSON["buffers"][0]["uri"];
	std::string filestr = std::string(file);
	std::string filedirectory = filestr.substr(0, filestr.find_last_of('/') + 1);
	bytetext = get_file_content((filedirectory + uri).c_str());
	std::cout << (filedirectory + uri) << std::endl;
	std::vector<unsigned char> data(bytetext.begin(), bytetext.end());
	return data;
}

std::vector<float> Model::getFloat(json accessor)
{
	std::vector<float> floatVec;
	unsigned int bufferviewindex = accessor.value("bufferView", 1);
	unsigned int count = accessor["count"];
	std::string type = accessor["type"];
	unsigned int accbyteoffset = accessor.value("byteOffset", 0);

	json bufferview = JSON["bufferViews"][bufferviewindex];
	unsigned int byteoffset = bufferview["byteOffset"];

	unsigned int variabletype;
	if (type == "SCALAR")variabletype = 1;
	else if (type == "VEC2")variabletype = 2;
	else if (type == "VEC3")variabletype = 3;
	else if (type == "VEC4")variabletype = 4;
	else throw std::invalid_argument("NOT SCALAR, VEC2,VEC3,VEC4");

	unsigned int beginingofdata = accbyteoffset + byteoffset;
	unsigned int lenghtofdata = count * 4 * variabletype;
	for (unsigned int i = beginingofdata;i < lenghtofdata;i)
	{
		unsigned char byte[] = { data[i++],data[i++],data[i++],data[i++] };
		float value;
		std::memcpy(&value, byte, sizeof(float));
		floatVec.push_back(value);
	}
	
	return floatVec;
}

std::vector<GLuint> Model::getIndices(json accessor)
{
	std::vector<GLuint> indices;

	unsigned int bufferviewindex = accessor.value("bufferView", 0);
	unsigned int count = accessor["count"];
	unsigned int component = accessor["componentType"];
	unsigned int accbyteoffset = accessor.value("byteOffset", 0);

	json bufferview = JSON["bufferViews"][bufferviewindex];
	unsigned int byteoffset = bufferview["byteOffset"];

	unsigned int beginingofdata = accbyteoffset + byteoffset;

	if (component == 5125)
	{
		for (unsigned int i = beginingofdata;i < beginingofdata + count * 4; i)
		{
			unsigned char byte[] = { data[i++],data[i++],data[i++],data[i++] };
			unsigned int value;
			std::memcpy(&value, byte, sizeof(unsigned int));
			indices.push_back((GLuint)value);
		}
	}
	else if (component == 5123)
	{
		for (unsigned int i = beginingofdata;i < beginingofdata + count * 2; i)
		{
			unsigned char byte[] = { data[i++],data[i++] };
			unsigned short value;
			std::memcpy(&value, byte, sizeof(unsigned short));
			indices.push_back((GLuint)value);
		}
	}
	else if (component == 5122)
	{
		for (unsigned int i = beginingofdata;i < beginingofdata + count * 2; i)
		{
			unsigned char byte[] = { data[i++],data[i++] };
			short value;
			std::memcpy(&value, byte, sizeof(short));
			indices.push_back((GLuint)value);
		}
	}
	return indices;
}

std::vector<Texture> Model::getTexture()
{
	std::vector<Texture> texture;
	std::string filestr = std::string(file);
	std::string filedirectory = filestr.substr(0, filestr.find_last_of('/') + 1);
	
	for (unsigned int i = 0;i < JSON["images"].size();i++)
	{
		std::string texturepath = JSON["images"][0]["uri"];

		if (texturepath.find("baseColor") != std::string::npos)
		{
			Texture diffuse = Texture((filedirectory + texturepath).c_str(), "diffuse", i, GL_RGB, GL_UNSIGNED_BYTE);
			texture.push_back(diffuse);
		}
		
	}

	return texture;
}

void Model::loadmesh(unsigned int meshindex)
{
	unsigned int positionindex = JSON["meshes"][meshindex]["primitives"][0]["attributes"]["POSITION"];
	unsigned int normalindex = JSON["meshes"][meshindex]["primitives"][0]["attributes"]["NORMAL"];
	unsigned int textureindex = JSON["meshes"][meshindex]["primitives"][0]["attributes"]["TEXTCOORD_0"];
	unsigned int indicesindex = JSON["meshes"][meshindex]["primitives"][0]["indices"];

	std::vector<float> veritces = getFloat(JSON["accessors"][positionindex]);
	std::vector<GLuint> indicies = getIndices(JSON["accessors"][indicesindex]);
	std::cout << veritces.size() << indicies.size() << std::endl;
	
}

void Model::traversenodes(unsigned int nextnode)
{
	json node = JSON["nodes"][nextnode];
	if (node.find("mesh") != node.end())
	{
		loadmesh(node["mesh"]);
	}
	else if (node.find("children")!=node.end())
	{
		for (unsigned int i = 0;i < node["children"].size();i++)
		{
			traversenodes(node["children"][i]);
		}
	}
}