import { AlertCircle, Download } from "lucide-react";
import CardA from "./CardA";
import { useState } from "react";
import ModalA from "./ModalA";
import Button from "./Button";
import { $ } from "../../axios";

function FileDownload() {
  const [modal, setModalOpen] = useState(false);
  const [error, setError] = useState<string | null>(null);

  const handleDownloadClick = () => {
    setModalOpen(true);
  };
  const fileId = 9090;
  const handleDownload = async () => {
    try {
      const response = await $.get(`/api/chatroom/files/download/${fileId}`, {
        headers: {
          Accept: "application/octet-stream",
        },
      });
      const blob = new Blob([response.data], {
        type: "appication/octet-stream",
      });

      const link = document.createElement("a");
      link.href = URL.createObjectURL(blob);
      link.download = "42-chat-downloaded-file.txt";
      link.click();
      URL.revokeObjectURL(link.href);
    } catch (error) {
      setError("Download failed. Please try again.");
    }
    setModalOpen(false);
  };

  return (
    <div>
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
      )}
    </div>
  );
}

export default FileDownload;
