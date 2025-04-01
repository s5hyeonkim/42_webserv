import { useEffect, useRef, useState } from "react";
import { getChattingList } from "../../query.ts";
import "./ChatDisplay.css";
import { User, useUserStore } from "../../User.ts";
// import OldChats from "./OldChat.tsx";
// import RecentChats from "./RecentChat.tsx";
import useContentStore, { Content } from "../../Content.ts";
import { useQuery } from "@tanstack/react-query";
import DisplayedChat from "./DisplayedChat.tsx";
import { Toast } from "./toast.tsx";

export function ChatDisplay() {
  const { data, isLoading } = useQuery({
    queryKey: ["chatting"],
    queryFn: getChattingList,
    staleTime: 1000,
    refetchOnMount: true,
    // refetchInterval: 1000,
  });
  // const { users, setUsers, setNewUsers, setDeletedUsers } = useUserStore();
  const { users, setUsers } = useUserStore();
  // const { contents, setContents, setOldContents, setRecentContents } = useContentStore();
  const { setContents, setDisplayedContents } = useContentStore();
  const [loading, setLoading] = useState(false);
  const [page, setPage] = useState(1);
  const itemsPerPage = 12;

  const scrollRef = useRef<HTMLDivElement | null>(null);
  console.log("chat data received");
  console.log(data);
  // const classifyComments = (contents: Content[]) => {
  //   const now = new Date();
  //   const recentComments = contents.filter(
  //     (content) => now.getTime() - Number(content.timestamp) <= 1000 * 60 * 5
  //   );
  //   const oldComments = contents.filter(
  //     (content) => now.getTime() - Number(content.timestamp) > 1000 * 60 * 5
  //   );
  //   return { recentComments, oldComments };
  // };
  const classifyUsers = (currentUsers: User[]) => {
    const deletedUsers = users?.filter(
      (user) => !currentUsers.some((u) => u.user_id === user.user_id)
    );
    const addedUsers = currentUsers.filter(
      (user) => !users?.some((u) => u.user_id === user.user_id)
    );
    return { addedUsers, deletedUsers };
  };
  const handleScroll = () => {
    if (!scrollRef.current) return;

    const { scrollTop, scrollHeight, clientHeight } = scrollRef.current;
    if (scrollTop + clientHeight >= scrollHeight - 10 && !loading) {
      // 스크롤이 맨 아래에 가까워지면 페이지 증가
      setLoading(true);
      setPage((prevPage) => prevPage + 1);
      setLoading(false);
    }
  };
  useEffect(() => {
    const currentUsers: User[] = data?.users ?? [];
    const currentData: Content[] = data?.contents ?? [];
    // const { recentComments, oldComments } = classifyComments(currentData);

    const newContents = currentData.slice(0, page * itemsPerPage);
    setDisplayedContents(newContents);
    setUsers(currentUsers);
    const { addedUsers, deletedUsers } = classifyUsers(currentUsers);
    deletedUsers?.forEach((user: User) => {
      Toast.info(`${user.user_name}님이 삭제되었습니다.`, {});
    });

    addedUsers?.forEach((user: User) => {
      Toast.success(`${user.user_name}님이 추가되었습니다.`, {});
    });
    // if (addedUsers.length > 0) {
    //   setUsers(currentUsers);
    //   setNewUsers(addedUsers);
    // }
    // if (deletedUsers.length > 0) {
    //   setDeletedUsers(deletedUsers);
    // }

    // setOldContents(oldComments);
    setContents(currentData);
    // setRecentContents(recentComments);
    if (scrollRef.current) {
      scrollRef.current.scrollTop = scrollRef.current.scrollHeight;
    }
  }, [data]);

  // useEffect(() => {
  //   if (scrollRef.current) {
  //     scrollRef.current.scrollTop = scrollRef.current.scrollHeight;
  //   }
  // });

  if (isLoading) {
    return <div>Loading...</div>;
  }

  return (
    <div className="chat-container" ref={scrollRef} onScroll={handleScroll}>
      {/* <OldChats /> */}
      {/* <RecentChats /> */}
      <DisplayedChat />
    </div>
  );
}

export default ChatDisplay;
