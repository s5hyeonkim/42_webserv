import "./Card.css";

type CardProps = {
  image: string;
  subhead: string;
  description: string;
};

const Card = ({ image, subhead, description }: CardProps) => {
  return (
    <div className="card-container">
      <div className="card-img">
        <img src={image} alt="Card" className="card-image" />
      </div>
      <div className="card-text">
        <h3>{subhead}</h3>
        <p className="card-description">{description}</p>
      </div>
    </div>
  );
};

export default Card;
