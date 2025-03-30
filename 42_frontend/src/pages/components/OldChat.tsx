import useContentStore from "../../Content";
import MessageItem from "./MessageItem";

function OldChats() {
  const { oldContents } = useContentStore();
  // console.log("old");
  // console.log(oldContents);
  return (
    <div>
      <h2>Old Chat Messages (More than 5 minutes ago)</h2>
      <ul>
        {oldContents.map((message) => (
          <MessageItem key={message.content_id} message={message} />
        ))}
      </ul>
    </div>
  );
}
export default OldChats;
