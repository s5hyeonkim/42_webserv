import React from "react";

interface ButtonProps {
  onClick: React.MouseEventHandler<HTMLButtonElement>;
  children: React.ReactNode;
  variant?: "primary" | "secondary";
  className?: string;
}

const Button: React.FunctionComponent<ButtonProps> = ({
  onClick,
  children,
  variant = "primary",
  className,
}) => {
  const baseStyle = "px-4 py-2 rounded-md font-semibold";
  const primaryStyle = "bg-blue-500 text-white hover:bg-blue-600";
  const secondaryStyle = "bg-gray-200 text-gray-700 hover:bg-gray-300";

  const buttonStyle = variant === "primary" ? primaryStyle : secondaryStyle;

  return (
    <button
      onClick={onClick}
      className={`${baseStyle} ${buttonStyle} ${className}`}
    >
      {children}
    </button>
  );
};

export default Button;
