import useContentStore from "../../Content";

function OldChats() {
  const { oldContents } = useContentStore();
  // console.log("old");
  // console.log(oldContents);
  return (
    <div>
      <h2>Old Chat Messages (More than 5 minutes ago)</h2>
      <ul>
        {oldContents.map((message) => (
          <li key={message.content_id}>
            <strong>{message.user_name}:</strong>{" "}
            {message.is_exist ? (
              <span>{message.content}</span>
            ) : (
              // <span>{message.data}</span>
              <div> 메시지가 삭제되었습니다. </div>
            )}
            <small>{message.timestamp}</small>
          </li>
        ))}
      </ul>
    </div>
  );
}

export default OldChats;
