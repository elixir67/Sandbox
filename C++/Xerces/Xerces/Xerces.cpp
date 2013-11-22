// Xerces.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SAX2ImageHandler.h"
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <fstream>

std::set<std::wstring> FindImages(const char * xmlFile)
{
    int b = 0;
    int a = 1/b;

    XMLPlatformUtils::Initialize();
    SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
    parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
    parser->setFeature(XMLUni::fgXercesSchema, true);
    parser->setFeature(XMLUni::fgXercesHandleMultipleImports, true);
    parser->setFeature(XMLUni::fgXercesSchemaFullChecking, false);
    parser->setFeature(XMLUni::fgXercesIdentityConstraintChecking, true);
    parser->setFeature(XMLUni::fgSAX2CoreNameSpacePrefixes, false);
    parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
    parser->setFeature(XMLUni::fgXercesDynamic, true);

        //
    //  Create our SAX handler object and install it on the parser, as the
    //  document and error handler.
    //
    SAX2ImageHandler handler;
    parser->setContentHandler(&handler);
    parser->setErrorHandler(&handler);

    //reset error count first
    handler.resetErrors();

    try
    {
        const unsigned long startMillis = XMLPlatformUtils::getCurrentMillis();
        parser->parse(xmlFile);
        const unsigned long endMillis = XMLPlatformUtils::getCurrentMillis();
        //duration = endMillis - startMillis;
    }
    catch (const OutOfMemoryException&)
    {
        //XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
        //errorOccurred = true;
    }
    catch (const XMLException& e)
    {
        //XERCES_STD_QUALIFIER cerr << "\nError during parsing: '" << xmlFile << "'\n"
        //    << "Exception message is:  \n"
        //    << StrX(e.getMessage()) << "\n" << XERCES_STD_QUALIFIER endl;
        //errorOccurred = true;
    }

    catch (...)
    {
        //XERCES_STD_QUALIFIER cerr << "\nUnexpected exception during parsing: '" << xmlFile << "'\n";
        //errorOccurred = true;
    }

    const std::set<std::wstring> & images = handler.Images();
    // And call the termination method
    XMLPlatformUtils::Terminate();

    return images;
}

int _tmain(int argc, _TCHAR* argv[])
{
    const char * xmlFile = "..\\TestData\\Appearance_TexCoord-Example.gml";
    const std::set<std::wstring> & images = FindImages(xmlFile);
	return 0;
}

