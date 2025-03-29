import { useEffect } from "react";
import { getChattingList } from "../../query.ts";
import "./ChatDisplay.css";
import { User, useUserStore } from "../../User.ts";
import OldChats from "./OldChat.tsx";
import RecentChats from "./RecentChat.tsx";
import useContentStore, { Content } from "../../Content.ts";
import { useQuery } from "@tanstack/react-query";

export function ChatDisplay() {
  // const { setUser } = useUserStore();
  const { data, isLoading } = useQuery({
    queryKey: ["chatting"],
    queryFn: getChattingList,
    staleTime: 1000,
    refetchOnMount: true,
  });
  const { users, setUsers, setNewUsers, setDeletedUsers } = useUserStore();
  const { setContents, setOldContents, setRecentContents } = useContentStore();

  console.log("data received");
  console.log(data);
  const classifyComments = (contents: Content[]) => {
    const now = new Date();
    const recentComments = contents.filter(
      (content) => now.getTime() - content.timestamp <= 1000 * 60 * 5
    );
    const oldComments = contents.filter(
      (content) => now.getTime() - content.timestamp > 1000 * 60 * 5
    );
    return { recentComments, oldComments };
  };

  const classifyUsers = (currentUsers: User[]) => {
    const deletedUsers = users?.filter(
      (user) => !currentUsers.some((u) => u.user_id === user.user_id)
    );
    const addedUsers = currentUsers.filter(
      (user) => !users?.some((u) => u.user_id === user.user_id)
    );
    return { addedUsers, deletedUsers };
  };
  useEffect(() => {
    const currentUsers: User[] = data?.users ?? [];
    const currentData: Content[] = data?.contents ?? [];

    const { recentComments, oldComments } = classifyComments(currentData);
    const { addedUsers, deletedUsers } = classifyUsers(currentUsers);

    if (addedUsers.length > 0) {
      setUsers(currentUsers);
      setNewUsers(addedUsers);
    }
    if (deletedUsers.length > 0) {
      setDeletedUsers(deletedUsers);
    }

    setOldContents(oldComments);
    setContents(currentData);
    setRecentContents(recentComments);
  }, [data]);

  if (isLoading) {
    return <div>Loading...</div>;
  }

  return (
    <div>
      <p>Chat Messages:</p>
      <OldChats />
      <RecentChats />
    </div>
  );
}

export default ChatDisplay;
