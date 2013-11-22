#pragma once

#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <string>
#include <vector>
#include <set>
XERCES_CPP_NAMESPACE_USE

class SAX2ImageHandler: public DefaultHandler
{
public:
    SAX2ImageHandler(void);
    ~SAX2ImageHandler(void);

    void startElement(const XMLCh* const uri, 
                      const XMLCh* const localname, 
                      const XMLCh* const qname, 
                      const Attributes& attrs);
    void endElement( const XMLCh* const uri,
        const XMLCh* const localname,
        const XMLCh* const qname);

    void characters(const XMLCh* const chars, const XMLSize_t length);

    const std::set<std::wstring> & Images(){return m_images;}

private:
    std::set<std::wstring> m_images;
    bool m_isImageElement;
};

