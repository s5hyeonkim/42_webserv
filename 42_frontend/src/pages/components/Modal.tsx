import { PropsWithChildren, useState } from "react";
import "./Modal.css";

interface ModalProps {
  isOpen: boolean;
  onClose: () => void;
  onSubmit: (query: string) => Promise<void>;
}
function Modal({
  isOpen,
  onClose,
  onSubmit,
  children,
}: PropsWithChildren<ModalProps>) {
  const [loading, setLoading] = useState(false);
  const [query, setQuery] = useState("");
  const [errorMessage, setErrorMessage] = useState("");
  const handleSubmit = async () => {
    // if (!query.trim()) return;
    setLoading(true);
    const error = await onSubmit(query);
    if (error != null) {
      setErrorMessage(error);
    } else {
      setLoading(false);
      onClose();
    }
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
        {errorMessage && <p style={{ color: "red" }}>{errorMessage}</p>}{" "}
        <button onClick={handleSubmit} disabled={loading}>
          {loading ? "로딩중..." : "Submit"}
        </button>{" "}
        <button onClick={onClose}>Close</button>
      </div>
    </div>
  );
}

export default Modal;
