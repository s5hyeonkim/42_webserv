import { Outlet } from "react-router-dom";
import "./ChatPage.css";
import ChatDisplay from "./components/ChatDisplay.tsx";
// import ChatInput from "./components/ChatInput.tsx";
// import FileInput from "./components/FileInput.tsx";
// import FileDownload from "./components/FileDownload.tsx";
import { ToastContainer } from "react-toastify";
import Input from "./components/Input.tsx";

const ChatPage = () => {
  console.log("this is chat page");
  return (
    <div style ={{padding: "20px"}}>
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
