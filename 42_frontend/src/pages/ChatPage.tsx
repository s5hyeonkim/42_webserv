import { Outlet } from "react-router-dom";
import "./ChatPage.css";
import ChatDisplay from "./components/ChatDisplay.tsx";
// import ChatInput from "./components/ChatInput.tsx";
// import FileInput from "./components/FileInput.tsx";
// import FileDownload from "./components/FileDownload.tsx";
import { ToastContainer } from "react-toastify";
import Input from "./components/Input.tsx";
import { useEffect } from "react";

const ChatPage = () => {
  console.log("this is chat page");
  useEffect(() => {
    const preventBack = (e: BeforeUnloadEvent) => {
      e.preventDefault();
      // e.returnValue = '';
    };
    const handlePopState = () => {
      window.history.pushState(null, "", window.location.href);
    };
    window.history.pushState(null, "", window.location.href);
    window.addEventListener("popstate", handlePopState);
    window.addEventListener("beforeunload", preventBack);
    return () => {
      window.removeEventListener("popstate", handlePopState);
      window.removeEventListener("beforeunload", preventBack);
    };
  });
  return (
    <div style={{ padding: "20px" }}>
      <Outlet />
      <ToastContainer />
      <ChatDisplay />
      <Input />
      {/* <ChatInput /> */}
      {/* <FileInput /> */}
      {/* <FileDownload /> */}
    </div>
  );
};

export default ChatPage;
