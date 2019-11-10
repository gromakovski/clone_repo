#pragma once

#include <odb/core.hxx>

#include <string>

class other_person {
public:
  other_person ();

  const std::string& email () const;
  void email (const std::string&);

  const std::string& get_name () const;
  std::string& set_name ();

  unsigned short getAge () const;
  void setAge (unsigned short);

private:
  std::string email_;
  std::string name_;
  unsigned short age_;
};

#pragma db object(other_person)
#pragma db member(other_person::email_) id
