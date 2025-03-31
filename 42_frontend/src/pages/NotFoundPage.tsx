// import { useState } from "react";
import { Outlet } from "react-router-dom";
// import { $ } from "../axios";
// import { AlertCircle, Download } from "lucide-react";
// import Button from "./components/Button";
// import ModalA from "./components/ModalA";
// import CardA from "./components/CardA";

// interface Contenta {
//   user_id: number;
//   user_name: string;
//   content_id: number;
//   content: string;
//   is_exist: boolean;
//   is_comment: boolean;
//   timestamp: number;
// }

// const MAX_FILE_SIZE = 1 * 1024 * 1024;
// const TYPE_ALLOWED = ["text/plain"];

const NotFoundPage = () => {
  // const [file, setFile] = useState<File | null>(null);
  // const [error, setError] = useState<string | null>(null);
  // const [modal, setModalOpen] = useState(false);

  // const handleFileChange = (e: React.ChangeEvent<HTMLInputElement>) => {
  //   const file = e.target.files ? e.target.files[0] : null;
  //   console.log("setfile");
  //   console.log(file);
  //   if (file) {
  //     if (file.size > MAX_FILE_SIZE) {
  //       setError("1mb 이상의 파일만 가능합니다.");
  //       setFile(null);
  //     } else if (!TYPE_ALLOWED.includes(file.type)) {
  //       setError("파일의 타입은 텍스트만 가능합니다.");
  //       setFile(null);
  //     } else {
  //       setFile(file);
  //       setError(null);
  //     }
  //   }
  // };

  // const handleSubmit = async (e: React.FormEvent): Promise<Contenta | null> => {
  //   // const handleSubmit = () => {
  //   console.log("file submit??");
  //   console.log(file);
  //   e.preventDefault();
  //   if (file == null) {
  //     setError("파일을 선택해주세요!");
  //     return null;
  //   }
  //   console.log("send file -ing");
  //   const response = await $.post(`/api/chatroom/files`, file, {
  //     headers: {
  //       "Content-Type": "application/x-www-form-urlencoded",
  //     },
  //   })
  //     .then((res) => {
  //       setError(null);
  //       return res.data;
  //     })
  //     .catch(() => setError("file upload failed. try again"));
  //   return response;
  // };

  console.log("not found page");

  // const handleDownloadClick = () => {
  //   setModalOpen(true);
  // };
  // const fileId = 9090;
  // const handleDownload = async () => {
  //   try {
  //     const response = await $.get(`/api/chatroom/files/download/${fileId}`, {
  //       headers: {
  //         Accept: "application/octet-stream",
  //       },
  //     });
  //     const blob = new Blob([response.data], {
  //       type: "appication/octet-stream",
  //     });

  //     const link = document.createElement("a");
  //     link.href = URL.createObjectURL(blob);
  //     link.download = "42-chat-downloaded-file.txt";
  //     link.click();
  //     URL.revokeObjectURL(link.href);
  //   } catch (error) {
  //     setError("Download failed. Please try again.");
  //   }
  //   setModalOpen(false);
  // };
  return (
    <div>
      <Outlet />
      <div>NotFOund</div>
      {/* <form onSubmit={handleSubmit} className="file-input-form">
        <input type="file" onChange={handleFileChange} />
        <button type="submit">Upload File</button>
      </form>
      <CardA
        className="p-2 flex justify-between items-center cursor-pointer"
        onClick={handleDownloadClick}
      >
        파일 다운로드
        <Download className="w-4 h-4" />
      </CardA>
      {modal && (
        <ModalA open={modal} onClose={() => setModalOpen(false)}>
          <div className="p-4">
            <p>다운로드를 진행하시겠습니까?</p>
            <div className="flex justify-end space-x-2 mt-4">
              <Button onClick={() => setModalOpen(false)}>Cancel</Button>
              <Button onClick={handleDownload} variant="primary">
                Download
              </Button>
            </div>
          </div>
        </ModalA>
      )}
      {error && (
        <div className="text-red-500 flex items-center">
          <AlertCircle className="w-4 h-4 mr-2" /> {error}
        </div>
      )} */}
    </div>
  );
};

export default NotFoundPage;
