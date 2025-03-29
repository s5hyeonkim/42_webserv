import { useState } from "react";
import { Outlet } from "react-router-dom";
import { $ } from "../axios";
import { AlertCircle, Download } from "lucide-react";
import Button from "./components/Button";
import ModalA from "./components/ModalA";
import CardA from "./components/CardA";
// import { Outlet, useLocation } from "react-router-dom";
// import DirectoryPage from "./DirectoryPage";
interface Contenta {
  user_id: number;
  user_name: string;
  content_id: number;
  content: string;
  is_exist: boolean;
  is_comment: boolean;
  timestamp: number;
}
const MAX_FILE_SIZE = 1 * 1024 * 1024;
const TYPE_ALLOWED = ["text/plain"];

const NotFoundPage = () => {
  const [file, setFile] = useState<File | null>(null);
  const [error, setError] = useState<string | null>(null);
  const [modal, setModalOpen] = useState(false);

  const handleFileChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const file = e.target.files ? e.target.files[0] : null;
    console.log("setfile");
    console.log(file);
    if (file) {
      if (file.size > MAX_FILE_SIZE) {
        setError("1mb 이상의 파일만 가능합니다.");
        setFile(null);
      } else if (!TYPE_ALLOWED.includes(file.type)) {
        setError("파일의 타입은 텍스트만 가능합니다.");
        setFile(null);
      } else {
        setFile(file);
        setError(null);
      }
    }
  };

  const handleSubmit = async (e: React.FormEvent): Promise<Contenta | null> => {
    // const handleSubmit = () => {
    console.log("file submit??");
    console.log(file);
    e.preventDefault();
    if (file == null) {
      setError("파일을 선택해주세요!");
      return null;
    }
    console.log("send file -ing");
    const response = await $.post(`/api/chatroom/files`, file, {
      headers: {
        "Content-Type": "application/x-www-form-urlencoded",
      },
    })
      .then((res) => {
        setError(null);
        return res.data;
      })
      .catch(() => setError("file upload failed. try again"));
    return response;
  };

  const handleDownloadClick = () => {
    setModalOpen(true);
  };
  const fileId = 9090;
  const handleDownload = async () => {
    try {
      // Make an API call to download the file
      const response = await $.get(`/api/chatroom/files/download/${fileId}`, {
        headers: {
          Accept: "application/octet-stream", // Expecting binary data
        },
      });
      // Get the file content as a Blob
      const blob = new Blob([response.data], {
        type: "appication/octec-stream",
      });

      // Create a link to download the file
      const link = document.createElement("a");
      link.href = URL.createObjectURL(blob);
      link.download = "42-chat-downloaded-file"; // Default file name
      link.click(); // Trigger download
      URL.revokeObjectURL(link.href); // Clean up the object URL
    } catch (error) {
      setError("Download failed. Please try again.");
    }
    setModalOpen(false);
  };
  console.log("not found page");

  return (
    <div>
      <Outlet />
      <div>NotFOund</div>
      <form onSubmit={handleSubmit} className="file-input-form">
        1 <input type="file" onChange={handleFileChange} />
        <button type="submit">Upload File</button>
      </form>
      <CardA
        className="p-2 flex justify-between items-center cursor-pointer"
        onClick={handleDownloadClick}
      >
        File available for download
        <Download className="w-4 h-4" />
      </CardA>
      {modal && (
        <ModalA open={modal} onClose={() => setModalOpen(false)}>
          <div className="p-4">
            <p>Do you want to download the file?</p>
            <div className="flex justify-end space-x-2 mt-4">
              <Button onClick={() => setModalOpen(false)}>Cancel</Button>
              <Button onClick={handleDownload} variant="primary">
                Download
              </Button>
            </div>
            1
          </div>
        </ModalA>
      )}
      {error && (
        <div className="text-red-500 flex items-center">
          <AlertCircle className="w-4 h-4 mr-2" /> {error}
        </div>
      )}
    </div>
  );
};

export default NotFoundPage;
