#include <iostream>
#include <filesystem>
#include <algorithm>
#include <fstream>

#include <hex.h>
#include <md5.h>
#include "FileSystemCrawler.h"


namespace sys = std::tr2::sys;

struct md5
{
	md5()
	{ }

	std::vector<byte> read_file(const std::string &filename)
	{
		std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
		std::ifstream::pos_type pos = ifs.tellg();

		std::vector<byte>  result(pos);

		if (pos.seekpos() != 0)
		{
			ifs.seekg(0, std::ios::beg);
			ifs.read((char *)&result[0], pos);
		}

		return result;

		
	}

	std::string operator () (const std::string &file)
	{	
		CryptoPP::MD5 hash;
		byte digest[CryptoPP::MD5::DIGESTSIZE];
		std::vector<byte> content = read_file(file);

		if (content.size() > 0)
			hash.CalculateDigest(digest, &content[0], content.size());
		else
			hash.CalculateDigest(digest, nullptr, content.size());

		CryptoPP::HexEncoder encoder;
		std::string output;
		encoder.Attach(new CryptoPP::StringSink(output));
		encoder.Put(digest, sizeof(digest));
		encoder.MessageEnd();

		return output;
	}
};


struct list_files
{
private:
	std::string level;
public:
	list_files(std::string level)
		: level(level)
	{ }

	void operator () (const std::string &directory)
	{
		sys::directory_iterator end_itr;
		sys::directory_iterator itr(directory);

		std::string l(level);
		std::for_each(itr, end_itr,
			[&l](sys::path path) {

			if (sys::is_directory(path))
			{
				std::cout << path.leaf() << std::endl;

				list_files ls(l + " ");
				ls(path.directory_string());
			}
			else
			{
				md5 _md5;

				std::string name(path.leaf());
				std::string full_path(path.file_string());

				std::cout << l << name << " " << _md5(full_path) << std::endl;
			}

		});
	}
};

std::vector<std::string> FileSystemCrawler::crawl(const std::vector<std::string> &dirs)
{
	std::for_each(dirs.begin(), dirs.end(),
				  list_files(""));

	return std::vector<std::string>();
}