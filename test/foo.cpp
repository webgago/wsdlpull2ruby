#include "ruby.h"
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


VALUE cTest;


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

extern "C" void Init_foo() {
  test();
  cTest = rb_define_class("Test", rb_cObject);
}
