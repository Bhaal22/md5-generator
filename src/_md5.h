#ifndef __MD5_H
#define __MD5_H

#include <iostream>
#include <filesystem>
#include <algorithm>
#include <fstream>
#include <regex>


#include <hex.h>
#include <md5.h>

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

    std::string lowerCaseOutput(output);
    std::transform(output.begin(), output.end(), lowerCaseOutput.begin(), ::tolower);

    return lowerCaseOutput;
  }
};

template <typename _Action>
struct list_files
{
private:
  _Action *_action;
  std::string _pattern;
  int level;

public:
  typedef void result_type;

  list_files(_Action &action, const std::string &pattern, int level)
    : _action(&action), _pattern(pattern), level(level)
  { }

  void _do(const std::string &directory)
  {
    sys::directory_iterator end_itr;
    sys::directory_iterator itr(directory);

    int l = level;
    _Action &action = *_action;

    std::for_each(itr, end_itr,
      [&l, &action, this](sys::path path) {

      if (sys::is_directory(path))
      {
        action.do_directory(path);

        list_files<_Action> ls(action, _pattern, l + 1);
        ls._do(path.directory_string());
      }
      else
      {
        md5 _md5;

        std::string full_path(path.file_string());
        
        std::tr1::regex rx(_pattern);
        if (std::tr1::regex_match(full_path.begin(), full_path.end(), rx))
        {
          action.do_file(path, _md5(full_path));
        }
      }

    });
  }

  void operator () (const std::string &directory)
  {
    _action->set_root(directory);
    _do(directory);
  }
};


#endif
