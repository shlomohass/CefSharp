#pragma once

#include "BrowserSettings.h"
#include "ClientAdapter.h"
#include "ScriptCore.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Threading;

namespace CefSharp
{
namespace WinForms
{
    public ref class WebView sealed : public Control, IWebBrowser
    {
    private:
        ManualResetEvent^ _initialized;
        BrowserSettings^ _settings;

        MCefRefPtr<ClientAdapter> _clientAdapter;
        BrowserCore^ _browserCore;
        MCefRefPtr<ScriptCore> _scriptCore;

        void Initialize(String^ address, BrowserSettings^ settings);
        void WaitForInitialized();

    protected:
        virtual void OnHandleCreated(EventArgs^ e) override;
        virtual void OnSizeChanged(EventArgs^ e) override;
        virtual void OnGotFocus(EventArgs^ e) override;

    public:
        virtual event PropertyChangedEventHandler^ PropertyChanged
        {
            void add(PropertyChangedEventHandler^ handler)
            {
                _browserCore->PropertyChanged += handler;
            }

            void remove(PropertyChangedEventHandler^ handler)
            {
                _browserCore->PropertyChanged -= handler;
            }
        }

        virtual event ConsoleMessageEventHandler^ ConsoleMessage;

        WebView()
        {
            Initialize("about:blank", gcnew BrowserSettings);
        }

        WebView(String^ address, BrowserSettings^ settings)
        {
            Initialize(address, settings);
        }

        property bool IsInitialized
        {
            bool get()
            {
                return
                    _clientAdapter.get() != nullptr &&
                    _clientAdapter->GetIsInitialized();
            }
        }

        virtual property bool IsLoading
        {
            bool get() { return _browserCore->IsLoading; }
        }

        virtual property bool CanGoBack
        { 
            bool get() { return _browserCore->CanGoBack; } 
        }

        virtual property bool CanGoForward
        { 
            bool get() { return _browserCore->CanGoForward; } 
        }

        virtual property int ContentsWidth
        {
            int get() { return _browserCore->ContentsWidth; }
            void set(int contentsWidth) { _browserCore->ContentsWidth = contentsWidth; }
        }

        virtual property int ContentsHeight
        {
            int get() { return _browserCore->ContentsHeight; }
            void set(int contentsHeight) { _browserCore->ContentsHeight = contentsHeight; }
        }

        virtual property String^ Address
        {
            String^ get() { return _browserCore->Address; }
            void set(String^ address) { _browserCore->Address = address; }
        }

        virtual property String^ Title
        {
            String^ get() { return _browserCore->Title; }
            void set(String^ title) { _browserCore->Title = title; }
        }

        virtual property String^ TooltipText
        {
            String^ get() { return _browserCore->TooltipText; }
            void set(String^ text) { _browserCore->TooltipText = text; }
        }

        virtual property IBeforePopup^ BeforePopupHandler
        {
            IBeforePopup^ get() { return _browserCore->BeforePopupHandler; }
            void set(IBeforePopup^ handler) { _browserCore->BeforePopupHandler = handler; }
        }

        virtual property IBeforeResourceLoad^ BeforeResourceLoadHandler
        {
            IBeforeResourceLoad^ get() { return _browserCore->BeforeResourceLoadHandler; }
            void set(IBeforeResourceLoad^ handler) { _browserCore->BeforeResourceLoadHandler = handler; }
        }

        virtual property IBeforeMenu^ BeforeMenuHandler
        {
            IBeforeMenu^ get() { return _browserCore->BeforeMenuHandler; }
            void set(IBeforeMenu^ handler) { _browserCore->BeforeMenuHandler = handler; }
        }

        virtual property IAfterResponse^ AfterResponseHandler
        {
            IAfterResponse^ get() { return _browserCore->AfterResponseHandler; }
            void set(IAfterResponse^ handler) { _browserCore->AfterResponseHandler = handler; }
        }

        virtual void OnInitialized();

        virtual void Load(String^ url);
        virtual void Stop();
        virtual void Back();
        virtual void Forward();
        virtual void Reload();
        virtual void Reload(bool ignoreCache);
        virtual void Print();

        void ExecuteScript(String^ script);
        Object^ EvaluateScript(String^ script);
        Object^ EvaluateScript(String^ script, TimeSpan timeout);

        virtual void SetNavState(bool isLoading, bool canGoBack, bool canGoForward);

        virtual void OnFrameLoadStart();
        virtual void OnFrameLoadEnd();

        virtual void RaiseConsoleMessage(String^ message, String^ source, int line);
    };
}}