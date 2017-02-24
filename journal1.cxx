// NX 10.0.0.24
// Journal created by Administrator on Tue Jan 10 11:14:18 2017 中国标准时间
//
#include <uf_defs.h>
#include <NXOpen/NXException.hxx>
#include <NXOpen/Session.hxx>
#include <NXOpen/Body.hxx>
#include <NXOpen/BodyCollection.hxx>
#include <NXOpen/Builder.hxx>
#include <NXOpen/DisplayableObject.hxx>
#include <NXOpen/Face.hxx>
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/Features_SewBuilder.hxx>
#include <NXOpen/NXObject.hxx>
#include <NXOpen/Part.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Preferences_PartModeling.hxx>
#include <NXOpen/Preferences_PartPreferences.hxx>
#include <NXOpen/SelectDisplayableObjectList.hxx>
#include <NXOpen/SelectFaceList.hxx>
#include <NXOpen/SelectObjectList.hxx>
#include <NXOpen/Session.hxx>
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
    //   Menu: 插入(S)->组合(B)->缝合(W)...
    // ----------------------------------------------
    NXOpen::Session::UndoMarkId markId1;
    markId1 = theSession->SetUndoMark(NXOpen::Session::MarkVisibilityVisible, NXString("\345\274\200\345\247\213", NXString::UTF8));
    
    NXOpen::Features::Feature *nullNXOpen_Features_Feature(NULL);
    
    if ( !workPart->Preferences()->Modeling()->GetHistoryMode() )
    {
        throw NXException::Create("Create or edit of a Feature was recorded in History Mode but playback is in History-Free Mode.");
    }
    
    NXOpen::Features::SewBuilder *sewBuilder1;
    sewBuilder1 = workPart->Features()->CreateSewBuilder(nullNXOpen_Features_Feature);
    
    sewBuilder1->SetTolerance(0.01);
    
    theSession->SetUndoMarkName(markId1, NXString("\347\274\235\345\220\210 \345\257\271\350\257\235\346\241\206", NXString::UTF8));
    
    NXOpen::Body *body1(dynamic_cast<NXOpen::Body *>(workPart->Bodies()->FindObject("PATCH_OPENINGS(6)")));
    bool added1;
    added1 = sewBuilder1->TargetBodies()->Add(body1);
    
    NXOpen::Body *body2(dynamic_cast<NXOpen::Body *>(workPart->Bodies()->FindObject("LINKED_FACE(2)")));
    bool added2;
    added2 = sewBuilder1->ToolBodies()->Add(body2);
    
    NXOpen::Body *body3(dynamic_cast<NXOpen::Body *>(workPart->Bodies()->FindObject("LINKED_FACE(3)")));
    bool added3;
    added3 = sewBuilder1->ToolBodies()->Add(body3);
    
    NXOpen::Body *body4(dynamic_cast<NXOpen::Body *>(workPart->Bodies()->FindObject("LINKED_FACE(4)")));
    bool added4;
    added4 = sewBuilder1->ToolBodies()->Add(body4);
    
    NXOpen::Session::UndoMarkId markId2;
    markId2 = theSession->SetUndoMark(NXOpen::Session::MarkVisibilityInvisible, NXString("\347\274\235\345\220\210", NXString::UTF8));
    
    theSession->DeleteUndoMark(markId2, NULL);
    
    NXOpen::Session::UndoMarkId markId3;
    markId3 = theSession->SetUndoMark(NXOpen::Session::MarkVisibilityInvisible, NXString("\347\274\235\345\220\210", NXString::UTF8));
    
    NXOpen::NXObject *nXObject1;
    nXObject1 = sewBuilder1->Commit();
    
    theSession->DeleteUndoMark(markId3, NULL);
    
    theSession->SetUndoMarkName(markId1, NXString("\347\274\235\345\220\210", NXString::UTF8));
    
    sewBuilder1->Destroy();
    
    // ----------------------------------------------
    //   Menu: 工具(T)->操作记录(J)->停止录制(S)
    // ----------------------------------------------
}
