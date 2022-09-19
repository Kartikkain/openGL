#ifndef OBJ_CLASS_H
#define OBJ_CLASS_H
#include <json/json.h>
#include"Mesh.h"

using json = nlohmann::json;

class Model
{
public :
	Model(const char* file);

private:
	const char* file;
	std::vector<unsigned char> data;
	json JSON;
	std::vector<unsigned char> getdata();
	std::vector<float> getFloat(json accessor);
	std::vector<GLuint> getIndices(json accessor);
	std::vector<Texture> getTexture();
	void loadmesh(unsigned int meshindex);
	void traversenodes(unsigned int nextnode);

	/*std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
	std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
	std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);*/
};
#endif // !OBJ_CLASS_H

