#include <poppler/goo/GooString.h>
#include <poppler/poppler/Object.h>
#include <poppler/poppler/Outline.h>
#include <poppler/poppler/PDFDoc.h>

#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>
#include <memory>

using json = nlohmann::json;

Outline::OutlineTreeNode makeOutlineNode(const json &outlineStructureNode) {
  Outline::OutlineTreeNode outlineNode{
      .title = outlineStructureNode.begin().key(),
      .destPageNum = outlineStructureNode.begin()->at(0),
      .children = {},
  };

  auto childrenStructureArray = outlineStructureNode.begin()->at(1);
  if (childrenStructureArray != nullptr) {
    outlineNode.children.reserve(childrenStructureArray.size());

    for (auto &childrenStructureNode : childrenStructureArray) {
      outlineNode.children.push_back(
          std::move(makeOutlineNode(childrenStructureNode)));
    }
  }

  return outlineNode;
}

std::vector<Outline::OutlineTreeNode>
makeOutlineNodesFrom(const std::string &structureFilePath) {
  std::ifstream outlineStructureFS(structureFilePath);
  json outlineStructure = json::parse(outlineStructureFS);

  std::vector<Outline::OutlineTreeNode> outlineNodes;
  outlineNodes.reserve(outlineStructure.size());

  for (const auto &outlineStructureNode : outlineStructure) {
    outlineNodes.push_back(std::move(makeOutlineNode(outlineStructureNode)));
  }

  return outlineNodes;
}

std::unique_ptr<PDFDoc> openDocument(const std::string &documentPath) {
  return std::make_unique<PDFDoc>(std::make_unique<GooString>(documentPath));
}

std::unique_ptr<PDFDoc> clearDocumentOutline(std::unique_ptr<PDFDoc> document) {
  Outline *outline = document->getOutline();
  int nOutlineItems = 0;
  if (outline->getItems() != nullptr) {
    int nOutlineItems = outline->getItems()->size();
  }
  while (nOutlineItems--) {
    outline->removeChild(nOutlineItems);
  }
  return std::move(document);
}

void updateDocumentOutline(std::string documentPath, std::string savePath,
                           std::string outlineStructurePath) {
  auto document = clearDocumentOutline(openDocument(documentPath));
  auto outline = document->getOutline();
  outline->setOutline(makeOutlineNodesFrom(outlineStructurePath));
  document->saveAs(GooString(savePath));
}

int protected_main(int argc, char **argv) {
  updateDocumentOutline("resources/ex1/vol1_mechanics.pdf",
                        "resources/ex1/Vol1_Mechanics.pdf",
                        "resources/ex1/MechanicsOutline.json");
  return EXIT_SUCCESS;
}

int main(int argc, char **argv) {
  try {
    return protected_main(argc, argv);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Uncaught exception" << std::endl;
  }
  return EXIT_FAILURE;
}