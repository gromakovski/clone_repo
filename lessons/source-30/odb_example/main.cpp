// file      : hello/driver.cxx
// copyright : not copyrighted - public domain

#include <memory>
#include <iostream>

#include <odb/database.hxx>
#include <odb/query.hxx>
#include <odb/transaction.hxx>
#include <odb/sqlite/forward.hxx>
#include <odb/sqlite/database.hxx>


#define DATABASE_SQLITE
#include "database.hxx"

// odb -d sqlite --generate-query person.hxx
#include "person.hxx"
#include "person-odb.hxx"

// odb -d sqlite --generate-query other_person.hxx
#include "other_person.hxx"
#include "other_person-odb.hxx"

using namespace std;
using namespace odb::core;

int
main (int argc, char* argv[])
{
  try
  {
    std::unique_ptr<odb::database> db (new odb::sqlite::database (argc, argv));

    unsigned long john_id;
    unsigned long jane_id;
    unsigned long joe_id;
    // Create a few persistent person objects.
    //
    {
      person john ("John", "Doe", 33);
      person jane ("Jane", "Doe", 32);
      person joe ("Joe", "Dirt", 30);

      // Simple transactions
      odb::transaction t (db->begin ());

      // Make objects persistent and save their ids for later use.
      //
      john_id = db->persist (john);
      jane_id = db->persist (jane);
      joe_id = db->persist (joe);

      t.commit ();
    }


    // Simple search
    using query = odb::query<person>;
    using result = odb::result<person>;
    
    unsigned short age;
    query q (query::first == "John" && query::age < query::_ref (age));

    for (age = 10; age < 100; age += 10) {
        result r (db->query<person> (q));
        for (result::iterator i(r.begin()); i != r.end(); ++i)
            std::cout << i->first();
    }

    // Simple update
    std::unique_ptr<person> joe(db->load<person>(joe_id));
    joe->age(joe->age() + 1);
    db->update(*joe);

  }
  catch (const odb::exception& e)
  {
    cerr << e.what () << endl;
    return 1;
  }
}