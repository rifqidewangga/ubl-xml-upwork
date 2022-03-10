#include "InvoiceGenerator.h"

InvoiceGenerator::InvoiceGenerator(const char* certPath, const char* certPwd) : xmlSigner(certPath, certPwd)
{
}

void InvoiceGenerator::Generate(Invoice invoice, std::string filepath)
{
    PopulateXml(invoice);
    WriteXMLToFile("../Samples/unsignedDoc.xml");
    xmlSigner.SignXML(xmlToSign, filepath.c_str());
}

std::string InvoiceGenerator::GetString(double val)
{
    std::ostringstream streamObj;
    streamObj << std::fixed;
    streamObj << std::setprecision(2);

    streamObj << val;

    return streamObj.str();
}

void InvoiceGenerator::PopulateXml(Invoice invoice)
{
    xmlToSign.Clear();
    
    xmlToSign.put_Tag("Invoice");
    xmlToSign.AddAttribute("xmlns", "urn:oasis:names:specification:ubl:schema:xsd:Invoice-2");
    xmlToSign.AddAttribute("xmlns:cac", "urn:oasis:names:specification:ubl:schema:xsd:CommonAggregateComponents-2");
    xmlToSign.AddAttribute("xmlns:cbc", "urn:oasis:names:specification:ubl:schema:xsd:CommonBasicComponents-2");
    xmlToSign.AddAttribute("xmlns:ext", "urn:oasis:names:specification:ubl:schema:xsd:CommonExtensionComponents-2");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionURI", "urn:oasis:names:specification:ubl:dsig:enveloped:xades");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures", true, "xmlns:sac", "urn:oasis:names:specification:ubl:schema:xsd:SignatureAggregateComponents-2");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures", true, "xmlns:sbc", "urn:oasis:names:specification:ubl:schema:xsd:SignatureBasicComponents-2");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures", true, "xmlns:sig", "urn:oasis:names:specification:ubl:schema:xsd:CommonSignatureComponents-2");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|cbc:ID", "urn:oasis:names:specification:ubl:signature:1");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|sbc:ReferencedSignatureID", "urn:oasis:names:specification:ubl:signature:Invoice");
    
    xmlToSign.UpdateChildContent("cbc:ProfileID", "reporting:1.0");
    xmlToSign.UpdateChildContent("cbc:ID", std::to_string(invoice.ID).c_str());
    xmlToSign.UpdateChildContent("cbc:UUID", invoice.UUID.c_str());
    xmlToSign.UpdateChildContent("cbc:IssueDate", invoice.IssueDate.c_str());
    xmlToSign.UpdateChildContent("cbc:IssueTime", invoice.IssueTime.c_str());
    xmlToSign.UpdateAttrAt("cbc:InvoiceTypeCode", true, "name", "0211010");
    xmlToSign.UpdateChildContent("cbc:InvoiceTypeCode", "388");
    xmlToSign.UpdateChildContent("cbc:DocumentCurrencyCode", "SAR");
    xmlToSign.UpdateChildContent("cbc:TaxCurrencyCode", "SAR");
    
    xmlToSign.UpdateChildContent("cac:BillingReference|cac:InvoiceDocumentReference|cbc:ID", invoice.BillingReferenceID.c_str());
    
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference|cbc:ID", "ICV");
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference|cbc:UUID", invoice.AdditionalReference1_UUID.c_str());
    
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference[1]|cbc:ID", "PIH");
    xmlToSign.UpdateAttrAt("cac:AdditionalDocumentReference[1]|cac:Attachment|cbc:EmbeddedDocumentBinaryObject", true, "mimeCode", "text/plain");
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference[1]|cac:Attachment|cbc:EmbeddedDocumentBinaryObject", invoice.PIH.c_str());
    
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference[2]|cbc:ID", "QR");
    xmlToSign.UpdateAttrAt("cac:AdditionalDocumentReference[2]|cac:Attachment|cbc:EmbeddedDocumentBinaryObject", true, "mimeCode", "text/plain");
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference[2]|cac:Attachment|cbc:EmbeddedDocumentBinaryObject", invoice.QRCode.c_str());
    
    xmlToSign.UpdateAttrAt("cac:Signature", true, "", "");
    xmlToSign.UpdateChildContent("cac:Signature|cbc:ID", "urn:oasis:names:specification:ubl:signature:Invoice");
    xmlToSign.UpdateChildContent("cac:Signature|cbc:SignatureMethod", "urn:oasis:names:specification:ubl:dsig:enveloped:xades");
    
    xmlToSign.UpdateAttrAt("cac:AccountingSupplierParty|cac:Party|cac:PartyIdentification|cbc:ID", true, "schemeID", "CRN");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PartyIdentification|cbc:ID", "1265126534");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:StreetName", "Kemarat Street,");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:BuildingNumber", "3724");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:PlotIdentification", "9833");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:CitySubdivisionName", "Alfalah");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:CityName", "Jeddah");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:PostalZone", "15385");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:CountrySubentity", "Makkah");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cac:Country|cbc:IdentificationCode", "SA");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PartyTaxScheme|cbc:CompanyID", "310122393500003");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PartyTaxScheme|cac:TaxScheme|cbc:ID", "VAT");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PartyLegalEntity|cbc:RegistrationName", "ILCACAO");
    
    xmlToSign.UpdateAttrAt("cac:AccountingCustomerParty|cac:Party|cac:PartyIdentification|cbc:ID", true, "schemeID", "NAT");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PartyIdentification|cbc:ID", "1010101010");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:StreetName", "Kemarat Street,");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:BuildingNumber", "3724");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:PlotIdentification", "9833");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:CitySubdivisionName", "Alfalah");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:CityName", "Jeddah");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:PostalZone", "15385");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:CountrySubentity", "Makkah");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cac:Country|cbc:IdentificationCode", "SA");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PartyLegalEntity|cbc:RegistrationName", "customer");

    xmlToSign.UpdateChildContent("cac:PaymentMeans|cbc:PaymentMeansCode", "10");
    xmlToSign.UpdateChildContent("cac:PaymentMeans|cbc:InstructionNote", invoice.InstructionNote.c_str());

    xmlToSign.UpdateAttrAt("cac:TaxTotal|cbc:TaxAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cbc:TaxAmount", GetString(invoice.TaxAmount).c_str());
    xmlToSign.UpdateAttrAt("cac:TaxTotal|cac:TaxSubtotal|cbc:TaxableAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cbc:TaxableAmount", GetString(invoice.TaxableAmount).c_str());
    xmlToSign.UpdateAttrAt("cac:TaxTotal|cac:TaxSubtotal|cbc:TaxAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cbc:TaxAmount", GetString(invoice.TaxAmount).c_str());
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cac:TaxCategory|cbc:ID", "Z");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cac:TaxCategory|cbc:Percent", GetString(invoice.VATPercent).c_str());
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cac:TaxCategory|cbc:TaxExemptionReasonCode", "VATEX-SA-HEA");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cac:TaxCategory|cbc:TaxExemptionReason", "Private healthcare to citizen");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cac:TaxCategory|cac:TaxScheme|cbc:ID", "VAT");
    
    xmlToSign.UpdateAttrAt("cac:TaxTotal[1]|cbc:TaxAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:TaxTotal[1]|cbc:TaxAmount", GetString(invoice.TaxAmount).c_str());
    
    xmlToSign.UpdateAttrAt("cac:LegalMonetaryTotal|cbc:LineExtensionAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:LegalMonetaryTotal|cbc:LineExtensionAmount", GetString(invoice.LineExtensionAmount).c_str());
    xmlToSign.UpdateAttrAt("cac:LegalMonetaryTotal|cbc:TaxExclusiveAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:LegalMonetaryTotal|cbc:TaxExclusiveAmount", GetString(invoice.TaxExclusiveAmount).c_str());
    xmlToSign.UpdateAttrAt("cac:LegalMonetaryTotal|cbc:TaxInclusiveAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:LegalMonetaryTotal|cbc:TaxInclusiveAmount", GetString(invoice.TaxInclusiveAmount).c_str());
    xmlToSign.UpdateAttrAt("cac:LegalMonetaryTotal|cbc:PayableAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:LegalMonetaryTotal|cbc:PayableAmount", GetString(invoice.PayableAmount).c_str());

    for (int i = 0; i < invoice.InvoiceLines.size(); i++)
    {
        auto invoiceLine = invoice.InvoiceLines[i];

        std::string temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cbc:ID";
        xmlToSign.UpdateChildContent(temp.c_str(), invoiceLine.ID.c_str());
        
        temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cbc:InvoicedQuantity";
        xmlToSign.UpdateAttrAt(temp.c_str(), true, "", "");
        xmlToSign.UpdateChildContent(temp.c_str(), std::to_string(invoiceLine.Quantity).c_str());

        temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cbc:LineExtensionAmount";
        xmlToSign.UpdateAttrAt(temp.c_str(), true, "currencyID", "SAR");
        xmlToSign.UpdateChildContent(temp.c_str(), GetString(invoiceLine.LineExtensionAmount).c_str());

        xmlToSign.UpdateAttrAt("cac:InvoiceLine|cac:TaxTotal|cbc:TaxAmount", true, "currencyID", "SAR");
        xmlToSign.UpdateChildContent("cac:InvoiceLine|cac:TaxTotal|cbc:TaxAmount", GetString(invoiceLine.TaxAmount).c_str());
        xmlToSign.UpdateAttrAt("cac:InvoiceLine|cac:TaxTotal|cbc:RoundingAmount", true, "currencyID", "SAR");
        xmlToSign.UpdateChildContent("cac:InvoiceLine|cac:TaxTotal|cbc:RoundingAmount", GetString(invoiceLine.RoundingAmount).c_str());

        temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cac:Item|cbc:Name";
        xmlToSign.UpdateChildContent(temp.c_str(), invoiceLine.Name.c_str());

        temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cac:Item|cac:ClassifiedTaxCategory|cbc:ID";
        xmlToSign.UpdateChildContent(temp.c_str(), "Z");

        temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cac:Item|cac:ClassifiedTaxCategory|cbc:Percent";
        xmlToSign.UpdateChildContent(temp.c_str(), GetString(invoice.VATPercent).c_str());

        temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cac:Item|cac:ClassifiedTaxCategory|cac:TaxScheme|cbc:ID";
        xmlToSign.UpdateChildContent(temp.c_str(), "VAT");
        
        temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cac:Price|cbc:PriceAmount";
        xmlToSign.UpdateAttrAt(temp.c_str(), true, "currencyID", "SAR");
        xmlToSign.UpdateChildContent(temp.c_str(), GetString(invoiceLine.PriceAmount).c_str());
    }

    /*
    xmlToSign.put_Tag("Invoice");
    xmlToSign.AddAttribute("xmlns", "urn:oasis:names:specification:ubl:schema:xsd:Invoice-2");
    xmlToSign.AddAttribute("xmlns:cac", "urn:oasis:names:specification:ubl:schema:xsd:CommonAggregateComponents-2");
    xmlToSign.AddAttribute("xmlns:cbc", "urn:oasis:names:specification:ubl:schema:xsd:CommonBasicComponents-2");
    xmlToSign.AddAttribute("xmlns:ext", "urn:oasis:names:specification:ubl:schema:xsd:CommonExtensionComponents-2");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionURI", "urn:oasis:names:specification:ubl:dsig:enveloped:xades");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures", true, "xmlns:sac", "urn:oasis:names:specification:ubl:schema:xsd:SignatureAggregateComponents-2");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures", true, "xmlns:sbc", "urn:oasis:names:specification:ubl:schema:xsd:SignatureBasicComponents-2");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures", true, "xmlns:sig", "urn:oasis:names:specification:ubl:schema:xsd:CommonSignatureComponents-2");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|cbc:ID", "urn:oasis:names:specification:ubl:signature:1");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|sbc:ReferencedSignatureID", "urn:oasis:names:specification:ubl:signature:Invoice");
    xmlToSign.UpdateChildContent("cbc:ProfileID", "reporting:1.0");
    xmlToSign.UpdateChildContent("cbc:ID", "1");
    xmlToSign.UpdateChildContent("cbc:UUID", "3cf5ee18-ee25-44ea-a444-2c37ba7f28be");
    xmlToSign.UpdateChildContent("cbc:IssueDate", "2021-02-25");
    xmlToSign.UpdateChildContent("cbc:IssueTime", "16:55:24");
    xmlToSign.UpdateAttrAt("cbc:InvoiceTypeCode", true, "name", "0211010");
    xmlToSign.UpdateChildContent("cbc:InvoiceTypeCode", "388");
    xmlToSign.UpdateChildContent("cbc:DocumentCurrencyCode", "SAR");
    xmlToSign.UpdateChildContent("cbc:TaxCurrencyCode", "SAR");
    xmlToSign.UpdateChildContent("cac:BillingReference|cac:InvoiceDocumentReference|cbc:ID", "156166151");
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference|cbc:ID", "ICV");
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference|cbc:UUID", "70");
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference[1]|cbc:ID", "PIH");
    xmlToSign.UpdateAttrAt("cac:AdditionalDocumentReference[1]|cac:Attachment|cbc:EmbeddedDocumentBinaryObject", true, "mimeCode", "text/plain");
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference[1]|cac:Attachment|cbc:EmbeddedDocumentBinaryObject", "NWZlY2ViNjZmZmM4NmYzOGQ5NTI3ODZjNmQ2OTZjNzljMmRiYzIzOWRkNGU5MWI0NjcyOWQ3M2EyN2ZiNTdlOQ==");
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference[2]|cbc:ID", "QR");
    xmlToSign.UpdateAttrAt("cac:AdditionalDocumentReference[2]|cac:Attachment|cbc:EmbeddedDocumentBinaryObject", true, "mimeCode", "text/plain");
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference[2]|cac:Attachment|cbc:EmbeddedDocumentBinaryObject", "AQ1PbWFyIEhvc3BpdGFsAg8zMTAxMjIzOTM1MDAwMDMDFDIwMjEtMDItMjVUMTY6NTU6MjRaBAYyNTAuMDAFBDAuMDAGLDdFQmF1VUxoNlZuYWY2MkhhUGlnR3pZaTYyOWQxVUQ5U2srbWVIUElrSEk9B7AzMDU2MzAxMDA2MDcyYTg2NDhjZTNkMDIwMTA2MDUyYjgxMDQwMDBhMDM0MjAwMDQ5NmU4YzQ5NDAzZmMwOTQ1YzhmNDAyNThjZGQyZDllOTMwMWE3OTIxMmE5M2E3YzhmZmFkOGVjMmQ4MTVjMjVmMmNiNGRkNWZlNTNmYjhlN2QwYjRhMDI2ZmNhNDU3MjM1MTNkNzdjMGUzMzhlOTE1MTY4ZTUwZDU5NDA0ZGI5NAggVbTkjeRbgd+euMq1bJapyUNKIkDT01t2ZKjLHDDjZmcJIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    xmlToSign.UpdateChildContent("cac:Signature|cbc:ID", "urn:oasis:names:specification:ubl:signature:Invoice");
    xmlToSign.UpdateChildContent("cac:Signature|cbc:SignatureMethod", "urn:oasis:names:specification:ubl:dsig:enveloped:xades");
    xmlToSign.UpdateAttrAt("cac:AccountingSupplierParty|cac:Party|cac:PartyIdentification|cbc:ID", true, "schemeID", "CRN");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PartyIdentification|cbc:ID", "1265126534");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:StreetName", "Kemarat Street,");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:BuildingNumber", "3724");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:PlotIdentification", "9833");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:CitySubdivisionName", "Alfalah");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:CityName", "Jeddah");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:PostalZone", "15385");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:CountrySubentity", "Makkah");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cac:Country|cbc:IdentificationCode", "SA");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PartyTaxScheme|cbc:CompanyID", "310122393500003");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PartyTaxScheme|cac:TaxScheme|cbc:ID", "VAT");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PartyLegalEntity|cbc:RegistrationName", "Omar Hospital");
    
    xmlToSign.UpdateAttrAt("cac:AccountingCustomerParty|cac:Party|cac:PartyIdentification|cbc:ID", true, "schemeID", "NAT");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PartyIdentification|cbc:ID", "1010101010");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:StreetName", "Kemarat Street,");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:BuildingNumber", "3724");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:PlotIdentification", "9833");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:CitySubdivisionName", "Alfalah");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:CityName", "Jeddah");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:PostalZone", "15385");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:CountrySubentity", "Makkah");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cac:Country|cbc:IdentificationCode", "SA");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PartyLegalEntity|cbc:RegistrationName", "customer");
    
    xmlToSign.UpdateChildContent("cac:PaymentMeans|cbc:PaymentMeansCode", "42");
    xmlToSign.UpdateChildContent("cac:PaymentMeans|cbc:InstructionNote", "Some notes");

    xmlToSign.UpdateAttrAt("cac:TaxTotal|cbc:TaxAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cbc:TaxAmount", "0.00");
    xmlToSign.UpdateAttrAt("cac:TaxTotal|cac:TaxSubtotal|cbc:TaxableAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cbc:TaxableAmount", "0.00");
    xmlToSign.UpdateAttrAt("cac:TaxTotal|cac:TaxSubtotal|cbc:TaxAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cbc:TaxAmount", "0.00");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cac:TaxCategory|cbc:ID", "Z");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cac:TaxCategory|cbc:Percent", "0");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cac:TaxCategory|cbc:TaxExemptionReasonCode", "VATEX-SA-HEA");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cac:TaxCategory|cbc:TaxExemptionReason", "Private healthcare to citizen");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cac:TaxCategory|cac:TaxScheme|cbc:ID", "VAT");
    xmlToSign.UpdateAttrAt("cac:TaxTotal[1]|cbc:TaxAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:TaxTotal[1]|cbc:TaxAmount", "0.00");
    xmlToSign.UpdateAttrAt("cac:LegalMonetaryTotal|cbc:LineExtensionAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:LegalMonetaryTotal|cbc:LineExtensionAmount", "250.00");
    xmlToSign.UpdateAttrAt("cac:LegalMonetaryTotal|cbc:TaxExclusiveAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:LegalMonetaryTotal|cbc:TaxExclusiveAmount", "250.00");
    xmlToSign.UpdateAttrAt("cac:LegalMonetaryTotal|cbc:TaxInclusiveAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:LegalMonetaryTotal|cbc:TaxInclusiveAmount", "250.00");
    xmlToSign.UpdateAttrAt("cac:LegalMonetaryTotal|cbc:PayableAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:LegalMonetaryTotal|cbc:PayableAmount", "250.00");
    xmlToSign.UpdateChildContent("cac:InvoiceLine|cbc:ID", "18373428");
    xmlToSign.UpdateChildContent("cac:InvoiceLine|cbc:InvoicedQuantity", "1");
    xmlToSign.UpdateAttrAt("cac:InvoiceLine|cbc:LineExtensionAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:InvoiceLine|cbc:LineExtensionAmount", "250.00");
    xmlToSign.UpdateAttrAt("cac:InvoiceLine|cac:TaxTotal|cbc:TaxAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:InvoiceLine|cac:TaxTotal|cbc:TaxAmount", "0.00");
    xmlToSign.UpdateAttrAt("cac:InvoiceLine|cac:TaxTotal|cbc:RoundingAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:InvoiceLine|cac:TaxTotal|cbc:RoundingAmount", "250.00");
    xmlToSign.UpdateChildContent("cac:InvoiceLine|cac:Item|cbc:Name", "Surgery");
    xmlToSign.UpdateChildContent("cac:InvoiceLine|cac:Item|cac:ClassifiedTaxCategory|cbc:ID", "Z");
    xmlToSign.UpdateChildContent("cac:InvoiceLine|cac:Item|cac:ClassifiedTaxCategory|cbc:Percent", "0");
    xmlToSign.UpdateChildContent("cac:InvoiceLine|cac:Item|cac:ClassifiedTaxCategory|cac:TaxScheme|cbc:ID", "VAT");
    xmlToSign.UpdateAttrAt("cac:InvoiceLine|cac:Price|cbc:PriceAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:InvoiceLine|cac:Price|cbc:PriceAmount", "250.00");
    */
}

void InvoiceGenerator::WriteXMLToFile(std::string path)
{
    CkStringBuilder unsignedXML;
    xmlToSign.GetXmlSb(unsignedXML);
    unsignedXML.WriteFile(path.c_str(), "utf-8", false);
}

