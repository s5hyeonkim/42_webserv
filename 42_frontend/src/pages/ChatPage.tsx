import { Outlet } from "react-router-dom";
import "./ChatPage.css";
import ChatDisplay from "./components/ChatDisplay.tsx";
import ChatInput from "./components/ChatInput.tsx";
import FileInput from "./components/FileInput.tsx";
import FileDownload from "./components/FileDownload.tsx";

const ChatPage = () => {
  return (
    <div>
      <Outlet />
      <ChatDisplay />
      <ChatInput />
      <FileInput />
      <FileDownload />
    </div>
  );
};

export default ChatPage;
