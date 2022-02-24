#pragma once

#include <iostream>

#include <CkXml.h>
#include <CkCert.h>
#include <CkCertChain.h>
#include <CkPrivateKey.h>
#include <CkPfx.h>
#include <CkStringBuilder.h>
#include <CkXmlDSig.h>

void PopulateSample(CkXml& doc);
void CreatePFX();
void WriteXMLToFile(CkXml& doc, const char* filepath);
bool VerifyXML(const char* filepath);
