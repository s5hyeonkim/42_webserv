// Card.tsx
import React from "react";

interface CardProps {
  children: React.ReactNode;
  className?: string;
  onClick: () => void;
}

const CardA: React.FunctionComponent<CardProps> = ({
  children,
  className,
  onClick,
}) => {
  return (
    <div
      className={`bg-white shadow-lg rounded-lg p-4 cursor-pointer ${className}`}
      onClick={onClick}
    >
      {children}
    </div>
  );
};

export default CardA;
