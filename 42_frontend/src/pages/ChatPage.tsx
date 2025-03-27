import { Outlet } from "react-router-dom";
import "./ChatPage.css";
import { useEffect } from "react";
// import { $ } from "../axios.ts";
import { getChattingList } from "../query.ts";
import { useQuery } from "@tanstack/react-query";
import { User, useUserStore } from "../User.ts";
import useContentStore, { Content } from "../Content.ts";
import ChatDisplay from "./components/ChatDisplay.tsx";
import ChatInput from "./components/ChatInput.tsx";
import FileInput from "./components/FileInput.tsx";

const ChatPage = () => {
  const { data, isLoading } = useQuery({
    queryKey: ["chatting"],
    queryFn: getChattingList,
    staleTime: 1000,
  });

  // const [data, setData] = useState<chatting>(); // State to store fetched data
  // const [loading, setLoading] = useState(true); // State to manage loading state

  // useEffect(() => {
  //   const fetchData = async () => {
  //     try {
  //       const res = await $.get(`/chatroom`);
  //       setData(res.data);
  //       setLoading(false);
  //     } catch (error) {
  //       console.error("Error fetching data:", error);
  //       setLoading(false);
  //     }
  //   };

  //   fetchData();
  // }, []);
  const { users, setUsers, setNewUsers, setDeletedUsers } = useUserStore();
  const { setContents, setOldContents, setRecentContents } = useContentStore();

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
    // const fetch = async () => {
    //   const res = await $.get(`/chatroom`);
    //   // setLoading(false);
    //   setContents(res.data);
    //   console.log(res);
    // };
    // fetch();
    // const categoryParam = match.params.category;
    // dispatch(listProducts(categoryP1aram));
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
      <Outlet />
      <ChatDisplay data={data} />
      <ChatInput />
      <FileInput />
      {/* <div>qweqweqweqw</div>.<div>{data}</div> */}
    </div>
  );
};

export default ChatPage;
2;
