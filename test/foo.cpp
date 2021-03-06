//#include "rice/Class.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include "xmlpull/XmlPullParser.h"
#include "xmlpull/XmlPullParserException.h"
#include "schemaparser/Annotation.h"
#include "schemaparser/SchemaParser.h"
#include "schemaparser/SchemaValidator.h"
#include "schemaparser/TypeContainer.h"
#include "schemaparser/SchemaParserException.h"
#include "wsdlparser/Soap.h"
using namespace std;
using namespace Schema;
using namespace WsdlPull;
using namespace Rice;

SchemaParser * sp;

void test() {
    string uri = "/home/anton/projects/ezags-client/public/WSDL/rZAGS/InquiryService.xsd";
    SchemaParser * sp = new SchemaParser(uri);

    sp->parseSchemaTag();
    cout << sp->getNamespace();
    cout << endl;
    cout << endl;

    std::string elemName;

    Schema::Element element;

    const Schema::SchemaParser::ElementList & el = sp->getElements();

    int n = 0;

    for ( Schema::SchemaParser::ElementList::const_iterator eli= el.begin();
          eli!=el.end();
          eli++,n++)
    {
        if (n !=0)
          std::cout<<n<<"."<<eli->getName()<<std::endl;
    }

    std::cout<<"Which element should I generate an instance for [1.."<<n-1<<"]?";
    n = 1;

    n++; // locate the element in the list (first element bydefault is <schema> so skip it
    for ( Schema::SchemaParser::ElementList::const_iterator eli1= el.begin();
        eli1!=el.end() && n ;
        eli1++,n--) element = *eli1;


    SchemaValidator * sv = new SchemaValidator(sp);
    sv->instance(element.getName(),(Schema::Type)element.getType());

    cout<<std::endl;
}

Object initialize(Object self, Object rb_string){
    self.iv_set("@foo", 42);
    return to_ruby(42);
}

Object instance(Object self){
    return self.iv_get("@foo");
}

class Test
{
    public:
      Test(const std::string & uri);
      std::string getUri();
      std::string getNamespace();
      std::string instance();

    private:
      std::string uri_;
      SchemaParser * sp;
      std::list < std::string > elements;
};

Test::Test(const std::string & uri)
{
  sp = new SchemaParser(uri);
  sp->parseSchemaTag();
  uri_ = uri;
}

std::string
Test::instance()
{
    std::string elemName;

    Schema::Element element;

    const Schema::SchemaParser::ElementList & el = sp->getElements();

    int n = 0;

    for ( Schema::SchemaParser::ElementList::const_iterator eli= el.begin();
          eli!=el.end();
          eli++,n++)
    {
        if (n !=0)
          elements.push_back(eli->getName());
    }

    n = 1;

    n++; // locate the element in the list (first element bydefault is <schema> so skip it
    for ( Schema::SchemaParser::ElementList::const_iterator eli1= el.begin();
        eli1!=el.end() && n ;
        eli1++,n--) element = *eli1;


    ostringstream oss (ostringstream::out);

    SchemaValidator * sv = new SchemaValidator(sp, oss);
    sv->instance(element.getName(),(Schema::Type)element.getType());
    return oss.str();
}

std::string
Test::getNamespace()
{
  return sp->getNamespace();
}

std::string
Test::getUri()
{
  return uri_;
}

extern "C" void Init_foo() {
  //test();

  Data_Type<Test> rb_cTest =
    define_class<Test>("Test")
    .define_constructor(Constructor<Test, std::string>())
    .define_method("uri", &Test::getUri)
    .define_method("instance", &Test::instance)
    .define_method("namespace", &Test::getNamespace);

  Data_Type<SchemaParser> rb_SchemaParser =
    define_class<SchemaParser>("SchemaParser")
    .define_constructor(Constructor<SchemaParser, string>())
    .define_method("parse", &SchemaParser::parseSchemaTag)
    .define_method("elements", &SchemaParser::getElements)
    .define_method("namespace", &SchemaParser::getNamespace);
}
