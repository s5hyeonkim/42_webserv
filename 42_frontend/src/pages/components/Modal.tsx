import { PropsWithChildren, useState } from "react";
import "./Modal.css";
import { useUserStore } from "../../User.ts";
import { $ } from "../../axios.ts";
import { useNavigate } from "react-router-dom";

interface ModalProps {
  isOpen: boolean;
  onClose: () => void;
}
1;
function Modal({ isOpen, onClose, children }: PropsWithChildren<ModalProps>) {
  const [loading, setLoading] = useState(false);
  const [query, setQuery] = useState(""); // Input state for search query
  const navigate = useNavigate();
  const { setUser } = useUserStore();
  // const [data5, setData] = useState<string | null>(null); // Fetched data state  // Simulated fetch function for demonstration
  const sendUserInfo = async () => {
    setLoading(true);
    try {
      const res = await $.post("/api/users/register", {
        user_name: query,
      });
      console.log("inputText: ");
      console.log(query);
      // const newUser = {
      //   user_id: res.data.user_id,
      //   user_name: res.data.user_name,
      // };
      // setUser(newUser);
      // const redirect = res.headers["location"];
      setUser({ user_id: res.data.user_id, user_name: res.data.user_name });
      console.log("data");
      console.log(res.data);
      console.log(res.data.user_id);
      console.log(res.data.user_name);
      navigate(res.data.redirect_url);
      // setError
      // setLoading(false);
    } catch (e) {
      console.error(e);
    }
    onClose();
    setLoading(false);
  };

  // console.log("Modal");
  if (!isOpen) return null; // Hide modal if not open
  return (
    <div className="modal-container" role="dialog" aria-modal="true">
      <div className="backdrop" onClick={onClose} />
      <div className="dialog-box">
        {children}{" "}
        {/* Render any passed content (like the h2 and description) */}
        <input
          type="text"
          placeholder="채팅방 입장을 위한 이름을 입력해주세요..."
          value={query}
          onChange={(e) => setQuery(e.target.value)} // Update query on input change
        />
        {/* {data && <p>{data}</p>} */}
        <button onClick={sendUserInfo} disabled={loading}>
          {loading ?? "로딩중"}
          Submit
        </button>
        <button onClick={onClose}>Close</button>
      </div>
    </div>
  );
}

export default Modal;
