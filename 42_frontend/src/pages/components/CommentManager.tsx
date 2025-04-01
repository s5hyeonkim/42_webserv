import { Content } from "../../Content";

type CommentManagerProps = {
  message: Content;
  onDelete: (content: Content) => void;
  onDownload?: (content_id: number) => void;
  handleClose: () => void;
};

const CommentManager = ({
  message,
  onDelete,
  onDownload,
  handleClose,
}: CommentManagerProps) => {
  return (
    <div
      style={{
        position: "fixed",
        top: "40%",
        left: "50%",
        width: "240px",
        height: "100px",
        transform: "translate(-50%, -50%)",
        background: "white",
        padding: "10px",
        borderRadius: "10px",
        boxShadow: "0 4px 10px rgba(0,0,0,0.2)",
        zIndex: 1000,
      }}
    >
      <p style={{ textAlign: "center" }}>메시지를 어떻게 처리할까요?</p>
      {onDownload && (
        <button
          onClick={() => {
            onDownload(message.content_id);
            handleClose();
          }}
          style={{
            position: "fixed",
            left: "35px",
            marginRight: "10px",
            padding: "1px 10px",
            cursor: "pointer",
          }}
        >
          다운로드
        </button>
      )}
      <button
        onClick={() => {
          if (window.confirm("정말 삭제하시겠습니까?")) {
            onDelete(message);
          }
          handleClose();
        }}
        style={{
          padding: "5px 10px",
          position: "fixed",
          left: "55px",
          bottom: "16px",
          // marginLeft: "10px",
          cursor: "pointer",
          background: "red",
          color: "white",
          borderRadius: "10px",
          boxShadow: "0 4px 5px rgba(0,0,0,0.2)",
        }}
      >
        삭제
      </button>
      <button
        onClick={handleClose}
        style={{
          // marginRight: "10px",
          position: "fixed",
          right: "15px",
          bottom: "16px",
          padding: "5px 10px",
          cursor: "pointer",
          background: "gray",
          color: "white",
          borderRadius: "10px",
          boxShadow: "0 4px 5px rgba(0,0,0,0.2)",
        }}
      >
        취소
      </button>
    </div>
  );
};

export default CommentManager;
