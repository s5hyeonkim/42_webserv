import { Outlet } from "react-router-dom";
import "./ChatPage.css";
import ChatDisplay from "./components/ChatDisplay.tsx";
import ChatInput from "./components/ChatInput.tsx";
import FileInput from "./components/FileInput.tsx";

const ChatPage = () => {
  return (
    <div>
      <Outlet />
      <ChatDisplay />
      <ChatInput />
      <FileInput />
    </div>
  );
};

export default ChatPage;
