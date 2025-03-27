import { Outlet } from "react-router-dom";

const NotFoundPage = () => {
  console.log("not found page");
  return (
    <div>
      <Outlet />
      <div>NotFOund</div>
    </div>
  );
};

export default NotFoundPage;
