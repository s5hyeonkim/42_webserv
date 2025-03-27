import { useUserStore } from "../../User.ts";
import useContentStore from "../../Content.ts";

function RecentChats() {
  // const { data, isLoading } = getChattingList();
  const {
    // user,
    // users,
    // setUsers,
    newUsers,
    // setNewUsers,
    deletedUsers,
    // setDeletedUsers,
  } = useUserStore();
  const {
    // setContents,
    // addContent,
    // setOldContents,
    recentContents,
    // setRecentContents,
    // deletedContents,
    // setDeletedContents,
  } = useContentStore();

  // if (isLoading) return <p> Chatting Page를 불러오고 있습니다.</p>;
  return (
    <div
      className="chat-display"
      style={{ maxHeight: "400px", overflowY: "scroll" }}
    >
      {recentContents.map((message) => (
        <div key={message.content_id} className="chat-message">
          <strong>{message.user_name}:</strong>{" "}
          {message.is_exist ? (
            <span>{message.content}</span>
          ) : (
            // <span>{message.data}</span>
            <div> 메시지가 삭제되었습니다. </div>
          )}
          <br />
          <small>{message.timestamp}</small>
        </div>
      ))}
      <ul>
        {deletedUsers?.map((user) => (
          <li key={user.user_id} style={{ color: "red" }}>
            {user.user_name} 님이 퇴장하셨습니다.
          </li>
        ))}
      </ul>
      <ul>
        {newUsers?.map((user) => (
          <li key={user.user_id} style={{ color: "green" }}>
            {user.user_name} 님이 입장하셨습니다.
          </li>
        ))}
      </ul>
    </div>
  );
}

export default RecentChats;
