#ifndef __SHADER_H__
#define __SHADER_H__

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	GLuint iD; //program id

	Shader(const std::string & vertexPath, const std::string & fragmentPath);
	void use(); //ʹ��/�������

	//����uniform�ĺ��� 
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
};


//uniform �� setter ����
void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(iD, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(iD, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(iD, name.c_str()), value);
}

//��ȡ�ļ������ɶ�ӦshaderCode�ַ���
const char * getCodeFromFile(const GLchar * filePath);
//����shader
GLuint createShader(const char * shaderCode, GLenum type);
//
std::string getRelativePath() {
	return "H:\\vs_workspace\\shader_source\\";
}

/**
 * vertexPath, fragmentPath
 ��H:\\vs_workspace\\shader_source\\hw\\01\\01.vs �����·�� hw\\01\\01.vs����
 */
Shader::Shader(const std::string & vertexPath, const std::string & fragmentPath)
{
	std::string vertexPath1 = getRelativePath() + vertexPath;
	std::string fragmentPath1 = getRelativePath() + fragmentPath;
	//1.ͨ��vs ps�ļ����code
	const char * vertexCode = getCodeFromFile(vertexPath1.c_str());
	const char * fragmentCode = getCodeFromFile(fragmentPath1.c_str());
	//2.����vs ps
	GLuint _vertexShader = createShader(vertexCode, GL_VERTEX_SHADER);
	GLuint _fragmentShader = createShader(fragmentCode, GL_FRAGMENT_SHADER);
	//3.����shader program
	iD = glCreateProgram();
	glAttachShader(iD, _vertexShader);
	glAttachShader(iD, _fragmentShader);
	glLinkProgram(iD);
	//check
	int success;
	char infoLog[512];
	glGetProgramiv(iD, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(iD, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(_vertexShader);
	glDeleteShader(_fragmentShader);
}

void Shader::use()
{
	glUseProgram(iD);
}

GLuint createShader(const char * shaderCode, GLenum type)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return shader;
}

const char * getCodeFromFile(const GLchar * filePath)
{
	std::string code;
	std::ifstream shaderFile;
	//��֤ifstream��������׳��쳣
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		//���ļ�
		shaderFile.open(filePath);
		std::stringstream shaderStream;
		//��ȡ�ļ��Ļ������ݵ���������
		shaderStream << shaderFile.rdbuf();
		//�ر��ļ�������
		shaderFile.close();
		//ת����������string
		code = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ [" << filePath << "]" << std::endl;
	}
	return _strdup(code.c_str());
}
#endif 
