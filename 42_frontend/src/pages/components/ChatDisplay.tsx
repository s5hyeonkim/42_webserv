import { useEffect } from "react";
// import useContentStore, { Content } from "../../Content.ts";
import { chatting } from "../../query.ts";
import "./ChatDisplay.css";
import { useUserStore } from "../../User.ts";
import OldChats from "./OldChat.tsx";
import RecentChats from "./RecentChat.tsx";
// import { useQuery } from "@tanstack/react-query";
// import { $ } from "../../axios.ts";

interface ChatDisplayProps {
  data: chatting | undefined; // Make sure it expects `data`
}
export function ChatDisplay(data: ChatDisplayProps) {
  const { setUser } = useUserStore();
  useEffect(() => {}, [data, setUser]);

  // if (isLoading) return <p> Chatting Page를 불러오고 있습니다.</p>;

  return (
    <div>
      <p>Chat Messages:</p>
      <OldChats />
      <RecentChats />
    </div>
  );
}

export default ChatDisplay;
