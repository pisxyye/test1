// NX 10.0.0.24
// Journal created by Administrator on Thu Feb 23 10:30:14 2017 中国标准时间
//
#include <uf_defs.h>
#include <NXOpen/NXException.hxx>
#include <NXOpen/Session.hxx>
#include <NXOpen/Assemblies_Component.hxx>
#include <NXOpen/Assemblies_ComponentAssembly.hxx>
#include <NXOpen/Builder.hxx>
#include <NXOpen/Die_DieLimitsBuilder.hxx>
#include <NXOpen/Edge.hxx>
#include <NXOpen/EdgeChainRule.hxx>
#include <NXOpen/Expression.hxx>
#include <NXOpen/ExpressionCollection.hxx>
#include <NXOpen/FaceFeatureRule.hxx>
#include <NXOpen/Features_ExtractFace.hxx>
#include <NXOpen/Features_Feature.hxx>
#include <NXOpen/Features_FeatureBuilder.hxx>
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/Features_PatchOpeningsBuilder.hxx>
#include <NXOpen/Features_Sew.hxx>
#include <NXOpen/GeometricUtilities_OnPathDimensionBuilder.hxx>
#include <NXOpen/NXObject.hxx>
#include <NXOpen/Part.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Point.hxx>
#include <NXOpen/Preferences_PartModeling.hxx>
#include <NXOpen/Preferences_PartPreferences.hxx>
#include <NXOpen/ScCollector.hxx>
#include <NXOpen/ScRuleFactory.hxx>
#include <NXOpen/SelectObject.hxx>
#include <NXOpen/SelectionIntentRule.hxx>
#include <NXOpen/Session.hxx>
#include <NXOpen/TaggedObject.hxx>
#include <NXOpen/Unit.hxx>
using namespace NXOpen;

extern "C" DllExport int ufusr_ask_unload()
{
    return (int)NXOpen::Session::LibraryUnloadOptionImmediately;
}

extern "C" DllExport void ufusr(char *param, int *retCode, int paramLen)
{
    NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());
    NXOpen::Part *displayPart(theSession->Parts()->Display());
    // ----------------------------------------------
    //   Menu: 插入(S)->曲面(R)->修补开口(P)...
    // ----------------------------------------------
    NXOpen::Session::UndoMarkId markId1;
    markId1 = theSession->SetUndoMark(NXOpen::Session::MarkVisibilityVisible, NXString("\345\274\200\345\247\213", NXString::UTF8));
    
    NXOpen::Features::Feature *nullNXOpen_Features_Feature(NULL);
    
    if ( !workPart->Preferences()->Modeling()->GetHistoryMode() )
    {
        throw NXException::Create("Create or edit of a Feature was recorded in History Mode but playback is in History-Free Mode.");
    }
    
    NXOpen::Features::PatchOpeningsBuilder *patchOpeningsBuilder1;
    patchOpeningsBuilder1 = workPart->Features()->CreatePatchOpeningsBuilder(nullNXOpen_Features_Feature);
    
    NXOpen::Die::DieLimitsBuilder *dieLimitsBuilder1;
    dieLimitsBuilder1 = patchOpeningsBuilder1->Limits();
    
    NXOpen::GeometricUtilities::OnPathDimensionBuilder *onPathDimensionBuilder1;
    onPathDimensionBuilder1 = dieLimitsBuilder1->Point1();
    
    NXOpen::GeometricUtilities::OnPathDimensionBuilder *onPathDimensionBuilder2;
    onPathDimensionBuilder2 = dieLimitsBuilder1->Point2();
    
    NXOpen::Expression *expression1(dynamic_cast<NXOpen::Expression *>(workPart->Expressions()->FindObject("p9")));
    expression1->SetRightHandSide("0");
    
    NXOpen::Expression *expression2(dynamic_cast<NXOpen::Expression *>(workPart->Expressions()->FindObject("p10")));
    expression2->SetRightHandSide("0");
    
    patchOpeningsBuilder1->ShelfLength()->SetRightHandSide("0");
    
    patchOpeningsBuilder1->ShelfRadius()->SetRightHandSide("0");
    
    patchOpeningsBuilder1->CutoutLength()->SetRightHandSide("0");
    
    patchOpeningsBuilder1->CutoutRadius()->SetRightHandSide("0");
    
    patchOpeningsBuilder1->Distance()->SetRightHandSide("0");
    
    theSession->SetUndoMarkName(markId1, NXString("\344\277\256\350\241\245\345\274\200\345\217\243 \345\257\271\350\257\235\346\241\206", NXString::UTF8));
    
    std::vector<NXOpen::Features::Feature *> features1(1);
    NXOpen::Features::Sew *sew1(dynamic_cast<NXOpen::Features::Sew *>(workPart->Features()->FindObject("SEW(5)")));
    features1[0] = sew1;
    NXOpen::Assemblies::Component *component1(dynamic_cast<NXOpen::Assemblies::Component *>(displayPart->ComponentAssembly()->RootComponent()->FindObject("COMPONENT prc__model1_wkpc 1")));
    NXOpen::FaceFeatureRule *faceFeatureRule1;
    faceFeatureRule1 = workPart->ScRuleFactory()->CreateRuleFaceFeature(features1, component1);
    
    std::vector<NXOpen::SelectionIntentRule *> rules1(1);
    rules1[0] = faceFeatureRule1;
    patchOpeningsBuilder1->Faces()->ReplaceRules(rules1, false);
    
    patchOpeningsBuilder1->FindOpenings(true);
    
    NXOpen::Features::ExtractFace *extractFace1(dynamic_cast<NXOpen::Features::ExtractFace *>(workPart->Features()->FindObject("LINKED_FACE(2)")));
    NXOpen::Edge *edge1(dynamic_cast<NXOpen::Edge *>(extractFace1->FindObject("EDGE * -5 * 1 {(70.8530004276378,8.4417530800881,69.5073409880641)(82.5208304588796,14.6766415826846,71.9191464267563)(71.3650407706693,21.2249183753649,75.8240345330277) LINKED_FACE(2)}")));
    NXOpen::Edge *nullNXOpen_Edge(NULL);
    NXOpen::Face *nullNXOpen_Face(NULL);
    NXOpen::EdgeChainRule *edgeChainRule1;
    edgeChainRule1 = workPart->ScRuleFactory()->CreateRuleEdgeChain(edge1, nullNXOpen_Edge, false, nullNXOpen_Face, false);
    
    std::vector<NXOpen::SelectionIntentRule *> rules2(1);
    rules2[0] = edgeChainRule1;
    patchOpeningsBuilder1->Openings()->ReplaceRules(rules2, false);
    
    std::vector<NXOpen::NXObject *> objectArray1;
    NXOpen::NXObject *nXObject1;
    patchOpeningsBuilder1->CreatePathFromOpening(objectArray1, &nXObject1);
    
    expression1->SetRightHandSide("0");
    
    expression2->SetRightHandSide("0");
    
    onPathDimensionBuilder1->Update(NXOpen::GeometricUtilities::OnPathDimensionBuilder::UpdateReasonPath);
    
    onPathDimensionBuilder2->Update(NXOpen::GeometricUtilities::OnPathDimensionBuilder::UpdateReasonPath);
    
    std::vector<NXOpen::NXObject *> objectArray2(1);
    objectArray2[0] = edge1;
    dieLimitsBuilder1->SetPathObjects(objectArray2);
    
    NXOpen::EdgeChainRule *edgeChainRule2;
    edgeChainRule2 = workPart->ScRuleFactory()->CreateRuleEdgeChain(edge1, nullNXOpen_Edge, false, nullNXOpen_Face, false);
    
    NXOpen::Features::ExtractFace *extractFace2(dynamic_cast<NXOpen::Features::ExtractFace *>(workPart->Features()->FindObject("LINKED_FACE(3)")));
    NXOpen::Edge *edge2(dynamic_cast<NXOpen::Edge *>(extractFace2->FindObject("EDGE * -5 * 1 {(67.706819403938,57.6157107787937,90.0740577297788)(48.8785803714339,46.8348307095194,93.1557084967894)(67.6558565484221,36.0249799116088,90.0759609842876) LINKED_FACE(2)}")));
    NXOpen::EdgeChainRule *edgeChainRule3;
    edgeChainRule3 = workPart->ScRuleFactory()->CreateRuleEdgeChain(edge2, nullNXOpen_Edge, false, nullNXOpen_Face, false);
    
    std::vector<NXOpen::SelectionIntentRule *> rules3(2);
    rules3[0] = edgeChainRule2;
    rules3[1] = edgeChainRule3;
    patchOpeningsBuilder1->Openings()->ReplaceRules(rules3, false);
    
    std::vector<NXOpen::NXObject *> objectArray3;
    NXOpen::NXObject *nXObject2;
    patchOpeningsBuilder1->CreatePathFromOpening(objectArray3, &nXObject2);
    
    NXOpen::EdgeChainRule *edgeChainRule4;
    edgeChainRule4 = workPart->ScRuleFactory()->CreateRuleEdgeChain(edge1, nullNXOpen_Edge, false, nullNXOpen_Face, false);
    
    NXOpen::EdgeChainRule *edgeChainRule5;
    edgeChainRule5 = workPart->ScRuleFactory()->CreateRuleEdgeChain(edge2, nullNXOpen_Edge, false, nullNXOpen_Face, false);
    
    NXOpen::Features::ExtractFace *extractFace3(dynamic_cast<NXOpen::Features::ExtractFace *>(workPart->Features()->FindObject("LINKED_FACE(4)")));
    NXOpen::Edge *edge3(dynamic_cast<NXOpen::Edge *>(extractFace3->FindObject("EDGE * -5 * 1 {(67.4924879661569,78.6842154534135,73.2948434638602)(78.6657629800666,85.2230851565486,71.5795481051774)(67.2925638006214,91.645033507462,71.1799166975467) LINKED_FACE(2)}")));
    NXOpen::EdgeChainRule *edgeChainRule6;
    edgeChainRule6 = workPart->ScRuleFactory()->CreateRuleEdgeChain(edge3, nullNXOpen_Edge, false, nullNXOpen_Face, false);
    
    std::vector<NXOpen::SelectionIntentRule *> rules4(3);
    rules4[0] = edgeChainRule4;
    rules4[1] = edgeChainRule5;
    rules4[2] = edgeChainRule6;
    patchOpeningsBuilder1->Openings()->ReplaceRules(rules4, false);
    
    std::vector<NXOpen::NXObject *> objectArray4;
    NXOpen::NXObject *nXObject3;
    patchOpeningsBuilder1->CreatePathFromOpening(objectArray4, &nXObject3);
    
    NXOpen::Session::UndoMarkId markId2;
    markId2 = theSession->SetUndoMark(NXOpen::Session::MarkVisibilityInvisible, NXString("\344\277\256\350\241\245\345\274\200\345\217\243", NXString::UTF8));
    
    theSession->DeleteUndoMark(markId2, NULL);
    
    NXOpen::Session::UndoMarkId markId3;
    markId3 = theSession->SetUndoMark(NXOpen::Session::MarkVisibilityInvisible, NXString("\344\277\256\350\241\245\345\274\200\345\217\243", NXString::UTF8));
    
    expression1->SetRightHandSide("0");
    
    expression2->SetRightHandSide("0");
    
    std::vector<NXOpen::SelectionIntentRule *> rules5(0);
    patchOpeningsBuilder1->DividingCurves()->ReplaceRules(rules5, false);
    
    NXOpen::Features::Feature *feature1;
    feature1 = patchOpeningsBuilder1->CommitFeature();
    
    theSession->DeleteUndoMark(markId3, NULL);
    
    theSession->SetUndoMarkName(markId1, NXString("\344\277\256\350\241\245\345\274\200\345\217\243", NXString::UTF8));
    
    NXOpen::Expression *expression3(patchOpeningsBuilder1->ShelfRadius());
    NXOpen::Expression *expression4(patchOpeningsBuilder1->ShelfLength());
    NXOpen::Expression *expression5(patchOpeningsBuilder1->Distance());
    NXOpen::Expression *expression6(patchOpeningsBuilder1->CutoutRadius());
    NXOpen::Expression *expression7(patchOpeningsBuilder1->CutoutLength());
    patchOpeningsBuilder1->Destroy();
    
    // ----------------------------------------------
    //   Menu: 工具(T)->操作记录(J)->停止录制(S)
    // ----------------------------------------------
}
