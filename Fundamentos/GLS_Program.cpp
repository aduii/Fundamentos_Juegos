#include "GLS_Program.h"
#include "Error.h"
#include <iostream>
#include <fstream>
#include <vector>

GLS_Program::GLS_Program(): programID(0),
	vertexShaderID(0),fragmentShaderID(0),numAtribute(0)
{
}

void GLS_Program::compileShader(const string& shaderPath, GLuint id)
{
	string fileContent = "";
	string line = "";
	ifstream shaderFile(shaderPath);
	if (shaderFile.fail()) {
		fatalError("No se puede abrir el archivo " + shaderPath);
	}
	while (getline(shaderFile,line)) {
		fileContent += line +"\n";
	}
	shaderFile.close();
	const char* contents = fileContent.c_str();
	glShaderSource(id, 1, &contents,nullptr);
	glCompileShader(id);

	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLenght = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLenght);
		std::vector<GLchar> infoLog(maxLenght);
		glGetShaderInfoLog(id, maxLenght, &maxLenght, &infoLog[0]);
		std::cout << shaderPath << endl;
		fatalError("Shader no compila " + printf("%s", &(infoLog[0])));
		glDeleteShader(id);
		return;
	}

}

GLS_Program::~GLS_Program()
{
}

void GLS_Program::addAtribute(const string& atributeName)
{
	glBindAttribLocation(programID, numAtribute++, atributeName.c_str());
}

void GLS_Program::use()
{
	glUseProgram(programID);
	for (int i = 0; i < numAtribute; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLS_Program::unuse()
{
	glUseProgram(0);
	for (int i = 0; i < numAtribute; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLS_Program::compileShaders(const string& vertexShaderFilePath, const string& fragmentShaderFilePath)
{
	programID = glCreateProgram();
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShaderID == 0) {
		fatalError("No se puede compilar el shader Vertex");
	}
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShaderID == 0) {
		fatalError("No se puede compilar el fragment Vertex");
	}
	compileShader(vertexShaderFilePath, vertexShaderID);
	compileShader(fragmentShaderFilePath, fragmentShaderID);
}

void GLS_Program::linkShader()
{
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);

	glLinkProgram(programID);
	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLenght = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLenght);
		std::vector<GLchar> infoLoght(maxLenght);
		glGetProgramInfoLog(programID, maxLenght, &maxLenght, &infoLoght[0]);
		glDeleteProgram(programID);
		fatalError("Shaders no se linkearon " + printf("%s", &(infoLoght[0])));

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		return;
	}
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

GLuint GLS_Program::getUniformLocation(const string& name)
{
	GLuint location = glGetUniformLocation(programID, name.c_str());
	if (location == GL_INVALID_INDEX) {
		fatalError("No se encuentra la variable " + name);
	}
	return location;
}
