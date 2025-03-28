import { PropsWithChildren, useState } from "react";
import "./Modal.css";
import { useUserStore } from "../../User.ts";
import { $ } from "../../axios.ts";
// import { useNavigate } from "react-router-dom";

interface ModalProps {
  isOpen: boolean;
  onClose: () => void;
}
function Modal({ isOpen, onClose, children }: PropsWithChildren<ModalProps>) {
  const [loading, setLoading] = useState(false);
  const [query, setQuery] = useState(""); // Input state for search query
  // const navigate = useNavigate();
  const { setUser } = useUserStore();

  const sendUserInfo = async () => {
    setLoading(true);
    try {
      const res = await $.post("/api/users/register", {
        user_name: query,
      }).then((res) => res.data);
      console.log("inputText: ");
      console.log(query);
      console.log("data");
      console.log(res);
      console.log(res.body);
      setUser(res.body);
      // navigate(res.redirect.redirect_url, { replace: true });
    } catch (e) {
      console.error(e);
    }
    onClose();
    setLoading(false);
  };

  if (!isOpen) return null;
  return (
    <div className="modal-container" role="dialog" aria-modal="true">
      <div className="backdrop" onClick={onClose} />
      <div className="dialog-box">
        {children}{" "}
        <input
          type="text"
          placeholder="채팅방 입장을 위한 이름을 입력해주세요..."
          value={query}
          onChange={(e) => setQuery(e.target.value)}
        />
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
