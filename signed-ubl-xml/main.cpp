#include <iostream>

#include <CkXml.h>
#include <CkXmlDSigGen.h>
#include <CkCert.h>
#include <CkStringBuilder.h>
#include <CkXmlDSig.h>

#include "Utility.h"
#include "XMLSigner.h"
#include "Invoice.h"
#include "InvoiceGenerator.h"

int main()
{
    InvoiceGenerator gen;

    Invoice invoice;
    invoice.ID = 1;
    invoice.UUID = "3cf5ee18-ee25-44ea-a444-2c37ba7f28be";
    invoice.IssueDate = "2021-02-25";
    invoice.IssueTime = "16:55:24";

    invoice.BillingReferenceID = "156166151";
    
    invoice.AdditionalReference1_UUID = "70";
    invoice.PIH = gen.GetPIH();
    
    invoice.PaymentMeansCode = "10";
    invoice.InstructionNote = "Some notes";

    invoice.TaxAmount = 0.0;
    invoice.TaxableAmount = 0.0;
    invoice.VATPercent = 0.0;
    
    invoice.LineExtensionAmount = 250.0;
    invoice.TaxExclusiveAmount = 250.0;
    invoice.TaxInclusiveAmount = 250.0;
    invoice.PayableAmount = 250.0;

    InvoiceLine invoiceLine;
    invoiceLine.ID = "18373428";
    invoiceLine.Quantity = 1;
    invoiceLine.LineExtensionAmount = 250.0;
    invoiceLine.Name = u8"شوكولاتة";
    invoiceLine.PriceAmount = 250.0;
    invoiceLine.TaxAmount = 0.0;
    invoiceLine.RoundingAmount = 250.0;

    invoice.InvoiceLines.push_back(invoiceLine);

    gen.Generate(invoice, "../Samples/signedDoc.xml");

    std::cout << "QR: " << gen.GetQR() << std::endl;
    std::cout << "PIH: " << gen.GetPIH() << std::endl;

    return 0;
}
