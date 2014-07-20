#include "stdafx.h"
#include "SAX2ImageHandler.h"

static const wchar_t * const IMAGE_URI = L"imageURI";

SAX2ImageHandler::SAX2ImageHandler(void)
    :m_isImageElement(false)
{
}


SAX2ImageHandler::~SAX2ImageHandler(void)
{
}

void SAX2ImageHandler::startElement(const XMLCh * const uri,
                                    const XMLCh * const localname,
                                    const XMLCh * const qname,
                                    const Attributes & attributes)
{
    if(0 == wcscmp(localname, IMAGE_URI))
        m_isImageElement = true;
}

void SAX2ImageHandler::endElement( const XMLCh* const uri,
        const XMLCh* const localname,
        const XMLCh* const qname)
{
     if(0 == wcscmp(localname, IMAGE_URI))
        m_isImageElement = false;
}

void SAX2ImageHandler::characters(const XMLCh* const chars, const XMLSize_t length)
{
    if(m_isImageElement)
    {
        std::wstring image = chars;
        m_images.insert(image);
    }
}
