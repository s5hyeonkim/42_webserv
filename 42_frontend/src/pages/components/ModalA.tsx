import React from "react";

interface ModalProps {
  open: boolean;
  onClose: () => void;
  children: React.ReactNode;
}

const ModalA: React.FunctionComponent<ModalProps> = ({
  open,
  onClose,
  children,
}) => {
  if (!open) return null;

  return (
    <div className="fixed inset-0 bg-black bg-opacity-50 flex justify-center items-center z-50">
      <div className="bg-white p-6 rounded-lg shadow-xl w-80">
        <div className="flex justify-end">
          <button
            onClick={onClose}
            className="text-gray-600 hover:text-gray-800"
          >
            X
          </button>
        </div>
        <div>{children}</div>
      </div>
    </div>
  );
};

export default ModalA;
